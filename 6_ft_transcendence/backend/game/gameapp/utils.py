import datetime
from typing import Any, Dict, List
from django.db import transaction
from django.http import QueryDict

from exceptions.CustomException import BadRequestFieldException
from gameapp.models import TempMatch, TempMatchRoom, TempMatchRoomUser, TempMatchUser
from gameapp.wsgi_utils import init_matches


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


def make_rooms(room_name: str, user_id: List[int]):
    with transaction.atomic():
        temp_match_room = TempMatchRoom.objects.create(room_name=room_name)

        temp_match_room_users: list[TempMatchRoomUser] = []
        for id in user_id:
            temp_match_user = TempMatchRoomUser.objects.create(
                user_id=id, temp_match_room_id=temp_match_room.id
            )
            temp_match_room_users.append(temp_match_user)

        user_len = len(user_id)

        prev_match = [
            TempMatch.objects.create(
                match_room_id=temp_match_room.id, round=2, winner_match=None
            )
        ]

        for round in [4, 8, 16]:
            if round > user_len:
                break

            match_len = round // 2
            cur_match = []

            for m in range(match_len):
                cur_match.append(
                    TempMatch.objects.create(
                        match_room_id=temp_match_room.id,
                        round=round,
                        winner_match_id=prev_match[m // 2].id,
                    )
                )

            prev_match = cur_match

        temp_match_users: list[TempMatchUser] = []
        for idx, match in enumerate(prev_match):
            temp_match_users.append(
                TempMatchUser.objects.create(
                    user_id=user_id[idx * 2],
                    temp_match_id=match.id,
                )
            )
            temp_match_users.append(
                TempMatchUser.objects.create(
                    user_id=user_id[idx * 2 + 1],
                    temp_match_id=match.id,
                )
            )

        init_matches(temp_match_users)
