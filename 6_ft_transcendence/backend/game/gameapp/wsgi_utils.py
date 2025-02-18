import logging
from typing import List, Tuple, Any

from django.db import transaction
from django.db.models import Min
from socketio.exceptions import ConnectionRefusedError

from exceptions.CustomException import InternalException
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
    get_match_user_or_none,
    get_str,
    generate_secret,
)

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

        init_matches(temp_match_users, match_tuples)


def make_airoom(user_id: int):
    room_name = generate_secret()
    with transaction.atomic():
        temp_match_room = TempMatchRoom.objects.create(room_name=room_name)
        temp_match_room_user = TempMatchRoomUser.objects.create(
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

        init_matches([temp_match_user], [], is_with_ai=True)


def _get_from_sess(sid: str) -> Tuple[int, str]:
    with sio_session(sid) as sess:
        user_id: int = sess["user_id"]
        user_name: str = sess["user_name"]

    return user_id, user_name


def clear_match_dict():
    match_dict.clear()


def _get_match_id_from_jwt(jwt) -> int:
    res = post(f"{JWT_URL}/jwt/check/ai", json={"jwt": jwt})
    if not res.ok:
        raise ConnectionRefusedError(res.content)

    json = res.json()
    return json["match_id"]


def _get_user_id_from_jwt(jwt) -> int:
    res = post(f"{JWT_URL}/jwt/check", json={"jwt": jwt, "skip_2fa": False})

    if not res.ok:
        raise ConnectionRefusedError(res.content)

    json = res.json()
    return json["user_id"]


def on_connect(sid, auth):
    logger.info(f"connected sid={sid}")

    # TODO: auth with JWT
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
    elif "jwt" in auth:
        jwt = get_str(auth, "jwt")
        user_id = _get_user_id_from_jwt(jwt)
        # TODO: Fix username
        user_name = fetch_username(user_id)
    else:
        user_id = int(auth["user_id"])
        user_name = auth["user_name"]

    with sio_session(sid) as sess:
        sess["is_ai"] = False
        sess["user_id"] = user_id
        sess["user_name"] = user_name

    room_user = get_room_user_or_none(user_id)
    if room_user is None or room_user.is_online:
        raise ConnectionRefusedError("temp match room user none or online")
    room_user.is_online = True
    room_user.save()
    logger.info(f"room_user, is_online is now True, {room_user}")

    room_name = room_user.temp_match_room.room_name
    sio_enter_room(sid, room_name)

    match_user = get_match_user_or_none(user_id)
    if match_user is None:
        raise ConnectionRefusedError("temp match user none")
    logger.info(f"match_user={match_user}")

    join_match(sid, match_user, username=user_name)


def on_disconnect(sid, reason):
    # TODO: If reason is CLIENT_DISCONNECT, wait to be reconnected

    with sio_session(sid) as sess:
        is_ai: bool = sess["is_ai"]
        if is_ai:
            return

        user_id: int = sess["user_id"]
        username: str = sess["user_name"]

    match_user = get_match_user_or_none(user_id)
    if match_user:
        match_id = match_user.temp_match.id
        match = match_dict.get(match_id)
        if match is not None:
            user = RealUser(is_ai=False, id=match_user.user.id, name=username, sid=sid)
            match.user_disconnected(user)
            logger.info(f"user_id={user_id} user disconnected")
        else:
            logger.info("disconnecting... but match_user not found")
    else:
        logger.info("disconnecting... but match_user not found")


def get_room_user_or_none(user_id: int):
    try:
        temp_match_room_user = TempMatchRoomUser.objects.get(user_id=user_id)
    except:
        temp_match_room_user = None
    return temp_match_room_user


def join_match_ai(sid: str, match_id: int):
    match_dict[match_id].ai_connected(sid)


def join_match(sid: str, match_user: TempMatchUser, username: str):
    room_id = match_user.temp_match.id
    created = False
    is_with_ai = match_user.temp_match.is_with_ai
    if room_id not in match_dict.get_dict():
        match_dict[room_id] = Match(match_user.temp_match, is_with_ai)
        created = True

    user = RealUser(is_ai=False, id=match_user.user.id, name=username, sid=sid)
    match_dict[room_id].user_connected(user)

    if is_with_ai:
        resp = post(f"{GAMEAI_URL}/ai/", json={"match_id": room_id})
        logger.info(f"request to ai has returned! OK={resp.ok}")


def clear_room(room_name: str):
    temp_room = TempMatchRoom.objects.get(room_name=room_name)
    room_user = TempMatchRoomUser.objects.filter(temp_match_room_id=temp_room.id)
    room_user.delete()

    temp_match = TempMatch.objects.filter(match_room_id=temp_room.id)
    temp_match_user = TempMatchUser.objects.filter(temp_match__in=temp_match)

    temp_match_user.delete()
    temp_match.delete()

    temp_room.delete()


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
    user_id, username = _get_from_sess(sid)
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
    users: List[TempMatchUser],
    matches: List[Tuple[TempMatch, TempMatch]],
    is_with_ai: bool = False,
):
    for u in users:
        match_id = u.temp_match.id
        if match_id not in match_dict.get_dict():
            match_dict[match_id] = Match(u.temp_match, is_with_ai=is_with_ai)

        user = RealUser(is_ai=False, id=u.user.id, name="", sid="")
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
