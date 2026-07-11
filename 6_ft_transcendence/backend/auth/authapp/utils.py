import datetime
import logging
from typing import Any, Dict, Tuple

from django.http import QueryDict
from requests import delete

from authapp.envs import FORTY_TWO_API_URL, JWT_URL, USER_URL
from authapp.models import User
from authapp.requests import get, post
from exceptions.CustomException import BadRequestFieldException, InternalException
from exceptions.CustomException import CustomException


logger = logging.getLogger(__name__)


def now() -> datetime.datetime:
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


def get_username_from_42(access_token) -> Tuple[int, str]:
    res = get(
        f"{FORTY_TWO_API_URL}/v2/me",
        headers={"Authorization": f"Bearer {access_token}"},
    )
    if not res.ok:
        raise InternalException()

    res_json = res.json()
    if "login" not in res_json or "id" not in res_json:
        raise InternalException()

    return int(res_json["id"]), res_json["login"]


def create_user(id_42: int, username: str) -> Tuple[str, str, bool]:
    user, created = User.objects.get_or_create(id_42=id_42)

    if created:
        try:
            resp = post(
                f"{USER_URL}/_internal/user",
                json={"user_id": user.id, "user_name": username},
            )
            if not resp.ok:
                logger.error(f"post Failed, resp={resp.text}")
                raise InternalException()
        except:
            user.delete()
            raise InternalException()

    resp = post(f"{JWT_URL}/jwt/token", json={"user_id": user.id, "twofa_delete": True})

    if not resp.ok:
        raise CustomException(resp.text, resp.status_code)

    resp_json = resp.json()
    return resp_json["access_token"], resp_json["refresh_token"], resp_json["isnew"]
