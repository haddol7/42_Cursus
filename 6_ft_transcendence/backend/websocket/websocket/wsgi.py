"""
WSGI config for websocket project.

It exposes the WSGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/5.1/howto/deployment/wsgi/
"""

import json
import os
import socketio

from logging import Logger
from typing import Any, List, TypedDict

from django.core.wsgi import get_wsgi_application
from socketio.exceptions import ConnectionRefusedError


from exceptions.CustomException import (
    CustomException,
    BadRequestFieldException,
    InternalException,
    UnauthenticatedException,
    WebSocketAlreadyRoomJoinedException,
    WebSocketRoomNotAdminException,
    WebSocketRoomNotFoundException,
    WebSocketRoomNotFullException,
    WebSocketRoomNotJoinedException,
)

from websocket.envs import JWT_URL, GAME_URL
from websocket.requests import post
from websocket.room import Room
from websocket.roomuser import RoomUser, RoomUserJson
from websocket.sio import (
    ROOM_CHANGED_EVENT,
    ROOM_LIMIT_VALID_VALUES,
    ROOM_LIST_EVENT,
    ROOM_LISTENERS,
    START_GAME_EVENT,
    sio,
    sio_emit,
)
from websocket.decorators import event_on
from websocket.userdict import UserDict
from websocket.utils import (
    fetch_username,
    get_int,
    get_joined_room,
    get_str,
)


os.environ.setdefault("DJANGO_SETTINGS_MODULE", "websocket.settings")

application = get_wsgi_application()
application = socketio.WSGIApp(sio, application)


logger = Logger(__name__)

sid_list = []


class PeopleListJson(TypedDict):
    people: List[RoomUserJson]


class RoomManager:
    room_list: List[Room]

    def __init__(self) -> None:
        self.room_list = []

    def room_list_to_json(self):
        room_json_list = [room.to_json() for room in self.room_list]
        return {"room": room_json_list}

    def add_room(self, room: Room):
        if room.room_id in [r.room_id for r in self.room_list]:
            raise InternalException()
        self.room_list.append(room)

    def remove_room(self, room: Room):
        self.room_list.remove(room)

    def _get_room(self, room_id: str) -> Room | None:
        for r in self.room_list:
            if r.room_id == room_id:
                return r
        return None

    def add_user(self, room_id: str, user_id: int):
        room = self._get_room(room_id)
        if room is None:
            raise WebSocketRoomNotFoundException()
        if not room.is_valid():
            self.remove_room(room)
            raise WebSocketRoomNotFoundException()
        room.add_user(user_id)

    def remove_user(self, room_id: str, user_id: int):
        room = self._get_room(room_id)
        if room is None:
            raise WebSocketRoomNotFoundException()
        if not room.is_valid():
            self.remove_room(room)
            raise WebSocketRoomNotFoundException()

        room.remove_user(user_id)
        if not room.is_valid():
            self.remove_room(room)

    def people_list_to_json(self, room_id: str) -> PeopleListJson:
        room = self._get_room(room_id)
        if room is None:
            raise WebSocketRoomNotFoundException()
        return {"people": room.people_list_to_json(user_dict)}


ROOM_MANAGER = RoomManager()

user_dict = UserDict()


def get_session_info(sid) -> int:
    with sio.session(sid) as sess:
        user_id: int | None = sess["user_id"]

    if user_id is None:
        raise UnauthenticatedException()

    return user_id


def _get_user_id_from_jwt(jwt: str) -> int:
    res = post(f"{JWT_URL}/jwt/check", json={"jwt": jwt, "skip_2fa": False})
    if not res.ok:
        logger.error(f"post failed, content={res.text}")
        raise ConnectionRefusedError(res.text)

    json = res.json()
    return json["user_id"]


def _connect(sid: str, environ, auth: dict[str, Any]):

    logger.info(f"auth={json.dumps(auth)}")

    if "jwt" in auth:
        jwt = get_str(auth, "jwt")
        user_id = _get_user_id_from_jwt(jwt)
        user_name = fetch_username(user_id)
        logger.info(
            f"from _get_user_id_from_Jwt: user_id={user_id}, user_name={user_name}"
        )
    else:
        logger.info("using deprecated method, user_id and user_name")
        user_id = auth["user_id"]
        if user_id is None:
            raise ConnectionRefusedError("bad_request:user_id")
        try:
            user_id = int(user_id)
        except:
            raise ConnectionRefusedError("bad_request:user_id")
        user_name = auth["user_name"]
        if user_name is None or not isinstance(user_name, str):
            raise ConnectionRefusedError("bad_request:user_name")

    with sio.session(sid) as sess:
        sess["user_id"] = user_id

    user_add_ret = user_dict.add(user_id, RoomUser(sid, user_id, user_name))
    if not user_add_ret:
        logger.info(f"userid={user_id} is in dict -> user.found")
        raise ConnectionRefusedError("user.found")

    logger.info(f"sid={sid} is entered to {ROOM_LISTENERS}")
    sio.enter_room(sid, ROOM_LISTENERS)
    sio_emit(ROOM_LIST_EVENT, ROOM_MANAGER.room_list_to_json(), to=sid)


@event_on("connect")
def connect(sid: str, environ, auth: dict[str, Any]):
    try:
        return _connect(sid, environ, auth)
    except CustomException as e:
        raise ConnectionRefusedError(e.msg)
    except ConnectionRefusedError as e:
        raise e
    except Exception as e:
        logger.error(f"While connecting, type = {type(e)}")
        logger.exception(e)
        raise ConnectionRefusedError("internal_error")


@event_on("disconnect")
def disconnect(sid: str, reason):
    logger.info(f"sid={sid} Disconnecting")
    user_id = get_session_info(sid)

    room_changed = False
    for r in sio.rooms(sid):
        if r == sid or r == ROOM_LISTENERS:
            continue
        ROOM_MANAGER.remove_user(r, user_id)
        room_changed = True
        sio_emit(ROOM_CHANGED_EVENT, ROOM_MANAGER.people_list_to_json(r), to=r)  # type: ignore

    if room_changed:
        sio_emit(ROOM_LIST_EVENT, ROOM_MANAGER.room_list_to_json(), to=ROOM_LISTENERS)

    user_dict.remove(user_id)


@event_on("make_room")
def sio_make_room(sid: str, data: dict[str, Any]):
    user_id = get_session_info(sid)

    room_name = get_str(data, "room_name", blank=False)
    room_limit = get_int(data, "room_limit")
    if room_limit not in ROOM_LIMIT_VALID_VALUES:
        raise BadRequestFieldException("room_limit")

    joined_room_id = get_joined_room(sid)
    if joined_room_id is not None:
        raise WebSocketAlreadyRoomJoinedException()

    logger.info(
        f"Server got make_room! title={room_name}, room_limit={room_limit}, user_id={user_id}"
    )
    room = Room(room_name=room_name, room_limit=room_limit, admin=user_id)
    ROOM_MANAGER.add_room(room)

    sio.leave_room(sid, room=ROOM_LISTENERS)
    sio_emit(ROOM_LIST_EVENT, ROOM_MANAGER.room_list_to_json(), to=ROOM_LISTENERS)

    sio.enter_room(sid, room=room.room_id)
    sio_emit(
        ROOM_CHANGED_EVENT,
        ROOM_MANAGER.people_list_to_json(room.room_id),  # type: ignore
        to=room.room_id,
    )


@event_on("enter_room")
def sio_enter_room(sid: str, data: dict[str, Any]):
    user_id = get_session_info(sid)

    room_id = get_str(data, "room_id")
    joined_room_id = get_joined_room(sid)
    if joined_room_id is not None:
        raise WebSocketAlreadyRoomJoinedException()

    ROOM_MANAGER.add_user(room_id, user_id)

    sio.leave_room(sid, ROOM_LISTENERS)
    sio_emit(ROOM_LIST_EVENT, ROOM_MANAGER.room_list_to_json(), to=ROOM_LISTENERS)

    sio.enter_room(sid, room_id)
    sio_emit(ROOM_CHANGED_EVENT, ROOM_MANAGER.people_list_to_json(room_id), to=room_id)  # type: ignore


@event_on("leave_room")
def sio_leave_room(sid: str, data: dict[str, Any]):
    user_id = get_session_info(sid)

    room_id = get_joined_room(sid)
    if room_id is None:
        logger.info("joined_room len = 0, user is not joined in any room")
        raise WebSocketRoomNotJoinedException()

    ROOM_MANAGER.remove_user(room_id, user_id)
    sio.leave_room(sid, room_id)
    sio_emit(ROOM_CHANGED_EVENT, ROOM_MANAGER.people_list_to_json(room_id), to=room_id)  # type: ignore

    sio.enter_room(sid, ROOM_LISTENERS)
    sio_emit(ROOM_LIST_EVENT, ROOM_MANAGER.room_list_to_json(), to=ROOM_LISTENERS)


@event_on("start_game")
def sio_start_game(sid: str, data: dict[str, Any]):
    user_id = get_session_info(sid)

    room_id = get_joined_room(sid)
    if room_id is None:
        logger.info("joined_room len = 0, user is not joined in any room")
        raise WebSocketRoomNotJoinedException()

    room = ROOM_MANAGER._get_room(room_id)
    if room is None:
        raise InternalException()
    elif not room.is_full():
        raise WebSocketRoomNotFullException()
    elif not room.is_admin(user_id):
        raise WebSocketRoomNotAdminException()

    resp = post(
        f"{GAME_URL}/_internal/game",
        json={
            "room_name": room.room_name,
            "users": room.people_list_to_json(user_dict),
        },
    )
    if not resp.ok:
        logger.error(f"resp error! {resp.text}")
        raise InternalException()

    sio_emit(START_GAME_EVENT, {}, to=room_id)


@event_on("debug")
def sio_debug(sid: str, data: dict[str, Any]):
    return {"rooms": sio.rooms(sid)}
