import logging
from typing import List, Tuple, Any

from django.db import transaction
from django.db.models import Min
from socketio.exceptions import ConnectionRefusedError

from exceptions.CustomException import InternalException
from gameapp.connect_utils import join_match
from gameapp.db_utils import get_room_user_or_none
from gameapp.envs import GAMEAI_URL, JWT_URL
from gameapp.match_objects import Match, match_dict
from gameapp.match_objects.matchuser import AI_ID, RealUser, get_dto
from gameapp.models import (
    TempMatch,
    TempMatchRoom,
    TempMatchRoomUser,
    TempMatchUser,
)
from gameapp.requests import post
from gameapp.sio import sio_enter_room, sio_session
from gameapp.utils import (
    fetch_username,
    get_int,
    get_match_room_user_or_none,
    get_match_user_or_none,
    get_str,
    generate_secret,
)
from gameapp.match_objects.waiting import Waiting, WaitingUsersJoin, waiting_dict

logger = logging.getLogger(__name__)


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

        match_tuples: list[Tuple[TempMatch, TempMatch]] = []

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
                if len(cur_match) % 2 == 0:
                    match_tuples.append((cur_match[-1], cur_match[-2]))

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

        init_matches(room_name, temp_match_users, match_tuples)


def make_airoom(user_id: int):
    room_name = generate_secret()
    with transaction.atomic():
        temp_match_room = TempMatchRoom.objects.create(room_name=room_name)
        TempMatchRoomUser.objects.create(
            user_id=user_id, temp_match_room_id=temp_match_room.id
        )

        temp_match = TempMatch.objects.create(
            match_room_id=temp_match_room.id,
            round=2,
            winner_match=None,
            is_with_ai=True,
        )

        temp_match_user = TempMatchUser.objects.create(
            user_id=user_id, temp_match_id=temp_match.id
        )

        init_matches(room_name, [temp_match_user], [], is_with_ai=True)


def _get_from_sess(sid: str) -> Tuple[bool, int, str]:
    with sio_session(sid) as sess:
        is_ai: bool = sess["is_ai"]
        user_id: int = sess["user_id"]
        user_name: str = sess["user_name"]

    return is_ai, user_id, user_name


def clear_match_dict():
    match_dict.clear()


def _get_match_id_from_jwt(jwt) -> int:
    try:
        res = post(f"{JWT_URL}/jwt/check/ai", json={"jwt": jwt})
    except InternalException as e:
        raise ConnectionRefusedError(e.msg)

    if not res.ok:
        raise ConnectionRefusedError(res.content)

    json = res.json()
    return json["match_id"]


def _get_user_id_from_jwt(jwt) -> int:
    try:
        res = post(f"{JWT_URL}/jwt/check", json={"jwt": jwt, "skip_2fa": False})
    except InternalException as e:
        raise ConnectionRefusedError(e.msg)

    if not res.ok:
        raise ConnectionRefusedError(res.content)

    json = res.json()
    return json["user_id"]


def on_connect(sid, auth):
    logger.info(f"connected sid={sid}")

    if "ai" in auth:
        jwt = get_str(auth, "jwt")
        match_id = _get_match_id_from_jwt(jwt)

        logger.info(f"AI joined with match_id={match_id}")
        join_match_ai(sid, match_id)

        with sio_session(sid) as sess:
            sess["is_ai"] = True
            sess["user_id"] = AI_ID
            sess["user_name"] = None
        return

    jwt = get_str(auth, "jwt")
    user_id = _get_user_id_from_jwt(jwt)
    user_name = fetch_username(user_id)
    user_dto: RealUser = get_dto(False, sid, user_id, user_name)  # type: ignore
    with sio_session(sid) as sess:
        sess["is_ai"] = False
        sess["user_id"] = user_id
        sess["user_name"] = user_name

    room_user = get_room_user_or_none(user_id)
    if room_user is None or room_user.is_online:
        raise ConnectionRefusedError("temp match room user none or online")

    logger.info(f"room_user, is_online is now True, {room_user}")

    room_name = room_user.temp_match_room.room_name
    sio_enter_room(sid, room_name)

    match_user = get_match_user_or_none(user_id)
    if match_user is None:
        logger.error(f"user_id={user_id} has room_user but has no match_user")
        raise ConnectionRefusedError("temp match user none")
    logger.info(f"match_user={match_user}")

    waiting_room = waiting_dict.get(room_name)
    if waiting_room is None:
        logger.error("cannot find waiting room! this is internal error")
        raise InternalException()
    waiting_room.user_join(user_dto)
    # join_match(sid, match_user, username=user_name)

    room_user.is_online = True
    room_user.save()


def on_disconnect(sid, reason):
    # TODO: If reason is CLIENT_DISCONNECT, wait to be reconnected

    is_ai, user_id, user_name = _get_from_sess(sid)
    if is_ai:
        return

    user_dto = RealUser(is_ai=False, id=user_id, name=user_name, sid=sid)

    match_room_user = get_match_room_user_or_none(user_id)
    if match_room_user is None:
        return
    room_name = match_room_user.temp_match_room.room_name
    waiting_room = waiting_dict.get(room_name)
    if waiting_room:
        ret = waiting_room.user_disconnect(user_dto)
        if ret:
            return

    match_user = get_match_user_or_none(user_id)
    if match_user:
        match_id = match_user.temp_match.id
        match = match_dict.get(match_id)
        if match is not None:
            match.user_disconnected(user_dto)
            logger.info(f"user_id={user_id} user disconnected")
        else:
            match_user.delete()
            match_room_user.delete()
            logger.info("disconnecting... but match not found")
            logger.error("Match Room User Not found could not be happening!!!")
    else:
        match_room_user.delete()
        logger.info("disconnecting... but match_user not found")


def join_match_ai(sid: str, match_id: int):
    match_dict[match_id].ai_connected(sid)


def on_paddle_move(sid: str, data: dict[str, Any]):
    logger.debug(f"paddle_move event received! sid={sid}, data={data}")

    with sio_session(sid) as sess:
        is_ai: bool = sess["is_ai"]
        user_id: int = sess["user_id"]
        user_name: str | None = sess["user_name"]
    logger.debug(f"sid={sid}, user_id={user_id}, user_name={user_name}, is_ai={is_ai}")

    user_dto = get_dto(is_ai, sid, user_id, user_name)
    room = match_dict.get_room_by_user_dto(user_dto)
    if room is None:
        logger.debug(f"sid={sid}, user_id={user_id} room not found")
        raise InternalException()

    paddle_direction = get_int(data, "paddleDirection")
    logger.debug(f"sid={sid}, paddle_direction={paddle_direction}")

    if room.match_process is not None:
        room.match_process.set_paddle(user_id, paddle_direction)


def on_next_game(sid: str):
    _, user_id, username = _get_from_sess(sid)
    logger.info(f"next_game event: sid={sid}, user_id={user_id}")

    user_min_match = TempMatch.objects.filter(tempmatchuser__user_id=user_id).aggregate(
        round=Min("round")
    )["round"]

    match_user = TempMatchUser.objects.filter(
        user_id=user_id, temp_match__round=user_min_match
    ).get()

    logger.info(match_user)
    logger.info(f"next match id = {match_user.temp_match.id}")

    join_match(sid, match_user, username)


def init_matches(
    room_name: str,
    users: List[TempMatchUser],
    matches: List[Tuple[TempMatch, TempMatch]],
    is_with_ai: bool = False,
):
    real_users = []
    for u in users:
        match_id = u.temp_match.id
        if match_id not in match_dict.get_dict():
            match_dict[match_id] = Match(u.temp_match, is_with_ai=is_with_ai)

        user = RealUser(is_ai=False, id=u.user.id, name="", sid="")
        real_users.append(user)

        logger.info(user)
        match_dict[match_id].user_decided(user)

    for m1, m2 in matches:
        match_id1 = m1.id
        if match_id1 not in match_dict.get_dict():
            match_dict[match_id1] = Match(m1, is_with_ai=is_with_ai)

        match_id2 = m2.id
        if match_id2 not in match_dict.get_dict():
            match_dict[match_id2] = Match(m2, is_with_ai=is_with_ai)

        match_dict[match_id1].add_listener(match_dict[match_id2])
        match_dict[match_id2].add_listener(match_dict[match_id1])

    waiting_dict.add(room_name, Waiting(real_users, room_name))
