import datetime
from typing import Any, Dict, List

from django.http import QueryDict

from exceptions.CustomException import BadRequestFieldException


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


def get_list(dict: Dict[str, Any] | QueryDict, key: str) -> List[Any]:
    val = _get_any(dict, key)
    if not isinstance(val, list):
        raise BadRequestFieldException(key)
    return val
