import datetime
import logging
import random
import string
from django.http import QueryDict
from typing import Any, Dict, List

from exceptions.CustomException import BadRequestFieldException, InternalException
from websocket.envs import USER_URL
from websocket.requests import get
from websocket.sio import sio, ROOM_LISTENERS

logger = logging.getLogger(__name__)


def now() -> datetime.datetime:
    return datetime.datetime.now(datetime.timezone.utc)


def _get_any(dict: Dict[str, Any] | QueryDict, key: str) -> Any:
    if key not in dict:
        raise BadRequestFieldException(key)
    if dict[key] is None:
        raise BadRequestFieldException(key)
    return dict[key]


def get_str(dict: Dict[str, Any] | QueryDict, key: str, blank: bool = True) -> str:
    val = _get_any(dict, key)

    if type(val) != str:
        raise BadRequestFieldException(key)
    if not blank and val == "":
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


def get_list(dict: Dict[str, Any] | QueryDict, key: str) -> List[Any]:
    val = _get_any(dict, key)
    if not isinstance(val, list):
        raise BadRequestFieldException(key)
    return val


def fetch_username(user_id: int) -> str:
    resp = get(f"{USER_URL}/_internal/user", params={"user_id": user_id})
    if not resp.ok:
        logger.error(f"request to user failed, msg={resp.text}")
        raise InternalException()

    resp_json = resp.json()
    logger.info(f"resp_json got {resp_json}")
    return resp_json


def generate_random(len: int) -> str:
    ret: str = ""
    for _ in range(len):
        ret += random.choice(string.ascii_letters + string.digits)
    return ret


def get_joined_room(sid: str) -> str | None:
    joined_room = [r for r in sio.rooms(sid) if r != sid and r != ROOM_LISTENERS]
    if len(joined_room) >= 2:
        logger.error(
            f"sid={sid}, join_room = {joined_room}, which could not be happening!"
        )
        raise InternalException()
    if len(joined_room) == 1:
        return joined_room[0]
    return None
