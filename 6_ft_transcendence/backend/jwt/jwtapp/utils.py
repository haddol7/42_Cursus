import datetime
import random
import string
from typing import Any, Dict, Tuple, TypedDict

from django.http import QueryDict
import jwt
import requests


from exceptions.CustomException import (
    BadRequestFieldException,
    CustomException,
    JwtExpiredException,
    JwtInvalidException,
    TwoFARegisterException,
)
from jwtapp.envs import (
    JWT_ALGORITHM,
    JWT_EXPIRE_SECONDS,
    JWT_REFRESH_EXPIRE_SECONDS,
    JWT_SECRET,
    TWOFA_URL,
)
from jwtapp.models import UserStatus


class JwtPayload(TypedDict):
    user_id: int
    user_secret: str
    exp: datetime.datetime


def _now() -> datetime.datetime:
    return datetime.datetime.now(datetime.timezone.utc)


def _get_any(dict: Dict[str, Any] | QueryDict, key: str) -> Any:
    if key not in dict:
        raise BadRequestFieldException(key)
    if dict[key] is None:
        raise BadRequestFieldException(key)
    return dict[key]


def get_str(dict: Dict[str, Any] | QueryDict, key: str) -> str:
    val = _get_any(dict, key)

    if type(val) != str:
        raise BadRequestFieldException(key)

    return val


def get_int(dict: Dict[str, Any] | QueryDict, key: str) -> int:
    val = _get_any(dict, key)

    try:
        ret = int(val)
    except:
        raise BadRequestFieldException(key)

    return ret


def get_bool(dict: Dict[str, Any] | QueryDict, key: str) -> bool:
    val = _get_any(dict, key)

    if type(val) == bool:
        return val
    elif type(val) == str:
        if val.lower() == "true":
            return True
        elif val.lower() == "false":
            return False

    raise BadRequestFieldException(key)


def generate_secret() -> str:
    LEN = 10
    ret: str = ""
    for _ in range(LEN):
        ret += random.choice(string.ascii_letters + string.digits)
    return ret


def _get_payload(user_id: int, user_secret: str, exp: datetime.datetime) -> JwtPayload:
    return {"user_id": user_id, "user_secret": user_secret, "exp": exp}


def _payloadToDict(payload: JwtPayload) -> Dict[str, Any]:
    return {
        "user_id": payload["user_id"],
        "user_secret": payload["user_secret"],
        "exp": payload["exp"],
    }


def _dictToPayload(decoded_jwt: Dict[str, Any]) -> JwtPayload:
    for key in JwtPayload.__required_keys__:
        if key not in decoded_jwt:
            raise JwtInvalidException()

    return {
        "user_id": decoded_jwt["user_id"],
        "user_secret": decoded_jwt["user_secret"],
        "exp": decoded_jwt["exp"],
    }


def _make_jwt(user_id: int, user_secret: str, exp: datetime.datetime) -> str:
    payload = _get_payload(user_id, user_secret, exp)
    decoded_Jwt = _payloadToDict(payload)
    token = jwt.encode(decoded_Jwt, key=JWT_SECRET, algorithm=JWT_ALGORITHM)

    return token


def _decode_payload(encoded_jwt: str) -> JwtPayload:
    try:
        decoded_jwt: Dict[str, Any] = jwt.decode(
            jwt=encoded_jwt,
            key=JWT_SECRET,
            algorithms=JWT_ALGORITHM,
            options={"require": ["exp"], "verify_exp": True},
        )
        payload: JwtPayload = _dictToPayload(decoded_jwt)
    except (jwt.exceptions.InvalidSignatureError, jwt.exceptions.DecodeError) as e:
        print("Jwt Invalid Signature", type(e))
        raise JwtInvalidException()
    except jwt.exceptions.ExpiredSignatureError as e:
        print("Jwt Expired Signature", type(e))
        raise JwtExpiredException()
    except Exception as e:
        raise e
    return payload


def set_user_secret(
    user_id: int, jwt_secret: str, refresh_secret: str, access_exp: datetime.datetime
) -> bool:
    user_obj, created = UserStatus.objects.update_or_create(
        user_id=user_id,
        defaults={
            "jwt_secret": jwt_secret,
            "refresh_secret": refresh_secret,
            "expired_at": access_exp,
        },
        create_defaults={
            "jwt_secret": jwt_secret,
            "refresh_secret": refresh_secret,
            "expired_at": access_exp,
        },
    )
    print(f"created={created}")
    print(f"set_user_secret = {user_id}, {jwt_secret}, {refresh_secret}, {access_exp}")

    if created:
        return created

    res = requests.delete(TWOFA_URL, params={"user_id": user_id})
    if not res.ok and res.text == TwoFARegisterException().__str__():
        created = True

    return created


def _get_user_status_or_none(user_id: int) -> UserStatus | None:
    try:
        user_status = UserStatus.objects.get(user_id=user_id)
    except UserStatus.DoesNotExist:
        user_status = None
    return user_status


def make_token_pair(user_id: int) -> Tuple[str, str, bool]:
    now_datetime = _now()
    access_exp = now_datetime + datetime.timedelta(seconds=JWT_EXPIRE_SECONDS)
    refresh_exp = now_datetime + datetime.timedelta(seconds=JWT_REFRESH_EXPIRE_SECONDS)

    jwt_secret = generate_secret()
    refresh_secret = generate_secret()
    isnew = set_user_secret(user_id, jwt_secret, refresh_secret, access_exp)

    access_token = _make_jwt(user_id, jwt_secret, access_exp)
    refresh_token = _make_jwt(user_id, refresh_secret, refresh_exp)

    return access_token, refresh_token, isnew


def check_jwt(encoded_jwt: str, skip_2fa: bool) -> JwtPayload:
    payload = _decode_payload(encoded_jwt)

    user_status = _get_user_status_or_none(payload["user_id"])
    if user_status is None:
        raise JwtInvalidException()
    if user_status.jwt_secret != payload["user_secret"]:
        print("secret not match")
        raise JwtInvalidException()

    if skip_2fa:
        return payload

    # Safety: JWT signature has verified, so we know this is safe to GET
    resp = requests.get(
        f"{TWOFA_URL}/twofa/check", params={"user_id": payload["user_id"]}
    )
    if not resp.ok:
        raise CustomException(resp.text, resp.status_code)

    return payload


def check_refresh_token(encoded_jwt: str) -> JwtPayload:
    payload = _decode_payload(encoded_jwt)

    user_status = _get_user_status_or_none(payload["user_id"])
    if user_status is None:
        raise JwtInvalidException()

    if user_status.refresh_secret != payload["user_secret"]:
        raise JwtInvalidException()

    return payload


def is_user_online(user_id: int) -> bool:
    user_status = _get_user_status_or_none(user_id)
    if user_status is None:
        return False

    return _now() < user_status.expired_at


def delete_token_secret(user_id: int):
    user_status = _get_user_status_or_none(user_id)
    if user_status is None:
        return
    user_status.jwt_secret = ""
    user_status.refresh_secret = ""
    user_status.expired_at = _now() - datetime.timedelta(seconds=1)
    user_status.save()
