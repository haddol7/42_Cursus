import datetime
import logging
import random
import string
from typing import Any, Dict, Tuple, TypedDict

import jwt
from django.http import QueryDict

from exceptions.CustomException import (
    BadRequestFieldException,
    CustomException,
    JwtExpiredException,
    JwtInvalidException,
    TwoFARegisterException,
)
from jwtapp.envs import (
    AI_USERID,
    JWT_AI_EXPIRE_SECONDS,
    JWT_ALGORITHM,
    JWT_EXPIRE_SECONDS,
    JWT_REFRESH_EXPIRE_SECONDS,
    JWT_SECRET,
    TWOFA_URL,
)
from jwtapp.models import UserStatus
from jwtapp.requests import delete, get

logger = logging.getLogger(__name__)


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


def _dict_to_payload(decoded_jwt: Dict[str, Any]) -> JwtPayload:
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


def _decode_payload(encoded_jwt: str) -> Dict[str, Any]:
    try:
        decoded_jwt: Dict[str, Any] = jwt.decode(
            jwt=encoded_jwt,
            key=JWT_SECRET,
            algorithms=JWT_ALGORITHM,
            options={"require": ["exp"], "verify_exp": True},
        )
    except (jwt.exceptions.InvalidSignatureError, jwt.exceptions.DecodeError) as e:
        logger.error(f"Jwt Invalid Signature {type(e)}")
        logger.exception(e)
        raise JwtInvalidException()
    except jwt.exceptions.ExpiredSignatureError as e:
        logger.error(f"Jwt Expired Signature {type(e)}")
        logger.exception(e)
        raise JwtExpiredException()
    except Exception as e:
        logger.error(
            f"while decode payload, unknown exception occurred, type={type(e)}"
        )
        logger.exception(e)
        raise e
    return decoded_jwt


def set_user_secret_only(
    user_id: int, jwt_secret: str, refresh_secret: str, access_exp: datetime.datetime
):
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
    return user_obj, created


def set_user_secret(
    user_id: int, jwt_secret: str, refresh_secret: str, access_exp: datetime.datetime
) -> bool:
    _, created = set_user_secret_only(user_id, jwt_secret, refresh_secret, access_exp)
    logger.info(f"created={created}")
    logger.info(
        f"set_user_secret = {user_id}, {jwt_secret}, {refresh_secret}, {access_exp}"
    )

    if created:
        return created

    res = delete(f"{TWOFA_URL}/twofa/check", params={"user_id": user_id})
    if not res.ok and res.text == TwoFARegisterException().__str__():
        created = True

    return created


def _get_user_status_or_none(user_id: int) -> UserStatus | None:
    try:
        user_status = UserStatus.objects.get(user_id=user_id)
    except UserStatus.DoesNotExist:
        user_status = None
    return user_status


def make_token_pair(user_id: int, twofa_delete: bool) -> Tuple[str, str, bool]:
    now_datetime = _now()
    access_exp = now_datetime + datetime.timedelta(seconds=JWT_EXPIRE_SECONDS)
    refresh_exp = now_datetime + datetime.timedelta(seconds=JWT_REFRESH_EXPIRE_SECONDS)

    jwt_secret = generate_secret()
    refresh_secret = generate_secret()
    if twofa_delete:
        isnew = set_user_secret(user_id, jwt_secret, refresh_secret, access_exp)
    else:
        _, isnew = set_user_secret_only(user_id, jwt_secret, refresh_secret, access_exp)

    access_token = _make_jwt(user_id, jwt_secret, access_exp)
    refresh_token = _make_jwt(user_id, refresh_secret, refresh_exp)

    return access_token, refresh_token, isnew


def check_jwt(encoded_jwt: str, skip_2fa: bool) -> JwtPayload:
    payload_dict = _decode_payload(encoded_jwt)
    payload = _dict_to_payload(payload_dict)

    user_status = _get_user_status_or_none(payload["user_id"])
    if user_status is None:
        raise JwtInvalidException()
    if user_status.jwt_secret != payload["user_secret"]:
        logger.info("secret not match, returning JwtInvalidException")
        raise JwtInvalidException()

    if skip_2fa:
        logger.info("skip_2fa is True, returning payload")
        return payload

    logger.info("skip 2fa is False, twofa check")
    # Safety: JWT signature has verified, so we know this is safe to GET
    resp = get(f"{TWOFA_URL}/twofa/check", params={"user_id": payload["user_id"]})
    if not resp.ok:
        raise CustomException(resp.text, resp.status_code)

    return payload


def check_refresh_token(encoded_jwt: str) -> JwtPayload:
    payload_dict = _decode_payload(encoded_jwt)
    payload = _dict_to_payload(payload_dict)

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


def get_ai_token(match_id: int) -> str:
    jwt_str = jwt.encode(
        {
            "user_id": AI_USERID,
            "match_id": match_id,
            "exp": _now() + datetime.timedelta(seconds=JWT_AI_EXPIRE_SECONDS),
        },
        key=JWT_SECRET,
        algorithm=JWT_ALGORITHM,
    )
    return jwt_str


def check_ai_token(encoded_jwt: str) -> int:
    try:
        decoded_dict = _decode_payload(encoded_jwt)
    except (JwtInvalidException, JwtExpiredException):
        raise JwtInvalidException()
    except Exception as e:
        logger.error("check ai token, decoded failed")
        logger.exception(e)
        raise e

    if "user_id" not in decoded_dict or decoded_dict["user_id"] != AI_USERID:
        raise JwtInvalidException()

    match_id: int = decoded_dict["match_id"]
    return match_id
