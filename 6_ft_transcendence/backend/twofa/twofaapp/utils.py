from typing import Any, Dict

from django.db import IntegrityError
from django.http import QueryDict

from exceptions.CustomException import BadRequestFieldException, NotFoundSthException
from twofaapp.models import UserInfo


def _get_any(dict: Dict[str, Any] | QueryDict, key: str):
    if key not in dict:
        raise BadRequestFieldException(key)
    if dict[key] is None:
        raise BadRequestFieldException(key)
    return dict[key]


def get_str(dict: Dict[str, Any] | QueryDict, key: str):
    val = _get_any(dict, key)

    if type(val) != str:
        raise BadRequestFieldException(key)

    return val


def get_int(dict: Dict[str, Any] | QueryDict, key: str):
    val = _get_any(dict, key)

    try:
        ret = int(val)
    except:
        raise BadRequestFieldException(key)

    return ret


def set_totp_secret(user_id: int, totp_secret: str, totp_name: str):
    try:
        user_obj, created = UserInfo.objects.update_or_create(
            user_id=user_id,
            defaults={"twofa_secret": totp_secret, "twofa_name": totp_name},
            create_defaults={"twofa_secret": totp_secret, "twofa_name": totp_name},
        )
    except IntegrityError:
        raise NotFoundSthException("user")


def get_userinfo_or_none(user_id: int):
    try:
        user_info = UserInfo.objects.get(user_id=user_id)
    except UserInfo.DoesNotExist:
        user_info = None
    return user_info
