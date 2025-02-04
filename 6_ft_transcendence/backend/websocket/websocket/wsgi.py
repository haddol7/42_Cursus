"""
WSGI config for websocket project.

It exposes the WSGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/5.1/howto/deployment/wsgi/
"""

import os
from typing import Dict, List, TypedDict
import socketio
import socketio.exceptions
from websocket.sio import sio

from django.core.wsgi import get_wsgi_application

from exceptions.CustomException import (
    BadRequestFieldException,
    InternalException,
    UnauthenticatedException,
    WebSocketAlreadyRoomJoinedException,
    WebSocketRoomFullException,
    WebSocketRoomNotAdminException,
    WebSocketRoomNotFoundException,
    WebSocketRoomNotFullException,
    WebSocketRoomNotJoinedException,
)

import random
import string

from websocket.decorators import event_on

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "websocket.settings")

application = get_wsgi_application()
application = socketio.WSGIApp(sio, application)


sid_list = []

ROOM_LISTENERS = "room_listeners"
ROOM_LIST_EVENT = "room_list"
ROOM_CHANGED_EVENT = "room_changed"
START_GAME_EVENT = "start_game"

ROOM_LIMIT_VALID_VALUES = [2, 4, 8, 16]


class RoomJson(TypedDict):
    room_id: str
    room_name: str
    room_limit: int
    room_cur_people: int


class RoomUserJson(TypedDict):
    user_id: int
    user_name: str


class RoomUser:
    sid: str
    user_id: int
    user_name: str
    room_name: str

    def __init__(self, sid: str, user_id: int, user_name: str) -> None:
        self.sid = sid
        self.user_id = user_id
        self.user_name = user_name

    def to_json(self) -> RoomUserJson:
        return {"user_id": self.user_id, "user_name": self.user_name}


class Room:
    room_id: str
    room_name: str
    room_limit: int
    user_list: List[int]

    def _get_random_str(self, n: int) -> str:
        ret: str = ""
        for _ in range(n):
            ret += random.choice(string.ascii_letters + string.digits)
        return ret

    def __init__(self, room_name: str, room_limit: int, admin: int) -> None:
        self.room_id = self._get_random_str(21)
        self.room_name = room_name
        self.room_limit = room_limit
        self.user_list = [admin]

    def to_json(self) -> RoomJson:
        return {
            "room_id": self.room_id,
            "room_name": self.room_name,
            "room_cur_people": len(self.user_list),
            "room_limit": self.room_limit,
        }

    def add_user(self, user_id: int) -> None:
        if not self.is_valid():
            raise WebSocketRoomNotFoundException()
        if len(self.user_list) >= self.room_limit:
            raise WebSocketRoomFullException()
        if user_id in self.user_list:
            raise WebSocketAlreadyRoomJoinedException()

        self.user_list.append(user_id)

    def remove_user(self, user_id: int) -> None:
        if not self.is_valid():
            raise WebSocketRoomNotFoundException()
        if user_id not in self.user_list:
            raise WebSocketRoomNotJoinedException()

        self.user_list.remove(user_id)

    def is_valid(self) -> bool:
        return len(self.user_list) > 0

    def people_list_to_json(self) -> List[RoomUserJson]:
        ret = []
        for u in self.user_list:
            ret.append(USER_DICT[u].to_json())
        return ret

    def is_full(self) -> bool:
        if not self.is_valid():
            return False
        return len(self.user_list) == self.room_limit

    def is_admin(self, user_id: int) -> bool:
        if not self.is_valid():
            return False
        return self.user_list[0] == user_id


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

    # def remove_room_by_name(self, room_id: str):
    #     self.room_list = [r for r in self.room_list if r.room_id != room_id]

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
        room.add_user(user_id)

    def remove_user(self, room_id: str, user_id: int):
        room = self._get_room(room_id)
        if room is None:
            raise WebSocketRoomNotFoundException()
        room.remove_user(user_id)
        if not room.is_valid():
            self.remove_room(room)

    def people_list_to_json(self, room_id: str) -> PeopleListJson:
        room = self._get_room(room_id)
        if room is None:
            return {"people": []}
        return {"people": room.people_list_to_json()}


ROOM_MANAGER = RoomManager()

USER_DICT: Dict[int, RoomUser] = {}


def get_session_info(sid) -> int:
    with sio.session(sid) as sess:
        user_id: int | None = sess["user_id"]

    if user_id is None:
        raise UnauthenticatedException()

    return user_id


@sio.event
def connect(sid, environ, auth):
    print("auth=", auth)
    user_id = auth["user_id"]
    user_name = auth["user_name"]

    if user_id is None:
        raise BadRequestFieldException("user_id")
    user_id = int(user_id)
    if user_name is None or not isinstance(user_name, str):
        raise BadRequestFieldException("user_name")

    if user_id in USER_DICT:
        print("userid is in dict")
        raise socketio.exceptions.ConnectionRefusedError("user.found")
    with sio.session(sid) as sess:
        sess["user_id"] = user_id
    USER_DICT[user_id] = RoomUser(sid, user_id, user_name)
    sio.enter_room(sid, ROOM_LISTENERS)
    sio.emit(ROOM_LIST_EVENT, ROOM_MANAGER.room_list_to_json(), to=sid)


@sio.event
def disconnect(sid, reason):
    print(f"sid={sid} Disconnecting")
    user_id = get_session_info(sid)

    room_changed = False
    for r in sio.rooms(sid):
        if r == sid or r == ROOM_LISTENERS:
            continue
        ROOM_MANAGER.remove_user(r, user_id)
        room_changed = True
        sio.emit(ROOM_CHANGED_EVENT, ROOM_MANAGER.people_list_to_json(r), to=r)

    if room_changed:
        sio.emit(ROOM_LIST_EVENT, ROOM_MANAGER.room_list_to_json(), to=ROOM_LISTENERS)

    del USER_DICT[user_id]


@event_on("make_room")
def sio_make_room(sid, data):
    user_id = get_session_info(sid)

    if "room_name" not in data:
        raise BadRequestFieldException("room_name")
    elif "room_limit" not in data:
        raise BadRequestFieldException("room_limit")

    room_name = data["room_name"]
    if room_name == "":
        raise BadRequestFieldException("room_name")

    room_limit = int(data["room_limit"])
    if room_limit not in ROOM_LIMIT_VALID_VALUES:
        raise BadRequestFieldException("room_limit")

    joined_room = [r for r in sio.rooms(sid) if r != sid and r != ROOM_LISTENERS]
    if len(joined_room) >= 1:
        raise WebSocketAlreadyRoomJoinedException()

    print(
        f"Server got make_room! title={room_name}, room_limit={room_limit}, user_id={user_id}"
    )
    room = Room(room_name=room_name, room_limit=room_limit, admin=user_id)
    ROOM_MANAGER.add_room(room)

    sio.leave_room(sid, room=ROOM_LISTENERS)
    sio.emit(ROOM_LIST_EVENT, ROOM_MANAGER.room_list_to_json(), to=ROOM_LISTENERS)

    sio.enter_room(sid, room=room.room_id)
    sio.emit(
        ROOM_CHANGED_EVENT,
        ROOM_MANAGER.people_list_to_json(room.room_id),
        to=room.room_id,
    )


@event_on("enter_room")
def sio_enter_room(sid, data):
    user_id = get_session_info(sid)

    if "room_id" not in data:
        raise BadRequestFieldException("room_id")
    joined_room = [r for r in sio.rooms(sid) if r != sid and r != ROOM_LISTENERS]
    if len(joined_room) >= 1:
        raise WebSocketAlreadyRoomJoinedException()

    room_id = data["room_id"]
    ROOM_MANAGER.add_user(room_id, user_id)

    sio.leave_room(sid, ROOM_LISTENERS)
    sio.emit(ROOM_LIST_EVENT, data=ROOM_MANAGER.room_list_to_json(), to=ROOM_LISTENERS)

    sio.enter_room(sid, room_id)
    sio.emit(ROOM_CHANGED_EVENT, ROOM_MANAGER.people_list_to_json(room_id), to=room_id)


@event_on("leave_room")
def sio_leave_room(sid):
    user_id = get_session_info(sid)

    joined_room = [r for r in sio.rooms(sid) if r != sid and r != ROOM_LISTENERS]
    if len(joined_room) == 0:
        raise WebSocketRoomNotJoinedException()
    elif len(joined_room) > 1:
        raise InternalException()
    room_id = joined_room[0]

    ROOM_MANAGER.remove_user(room_id, user_id)
    sio.leave_room(sid, room_id)
    sio.emit(ROOM_CHANGED_EVENT, ROOM_MANAGER.people_list_to_json(room_id), to=room_id)

    sio.enter_room(sid, ROOM_LISTENERS)
    sio.emit(ROOM_LIST_EVENT, ROOM_MANAGER.room_list_to_json(), to=ROOM_LISTENERS)


@event_on("start_game")
def sio_start_game(sid):
    user_id = get_session_info(sid)

    joined_room = [r for r in sio.rooms(sid) if r != sid and r != ROOM_LISTENERS]
    if len(joined_room) == 0:
        raise WebSocketRoomNotJoinedException()
    elif len(joined_room) > 1:
        raise InternalException()

    room_id = joined_room[0]
    room = ROOM_MANAGER._get_room(room_id)

    if room is None:
        raise InternalException()

    if not room.is_full():
        raise WebSocketRoomNotFullException()
    elif not room.is_admin(user_id):
        raise WebSocketRoomNotAdminException()

    sio.emit(START_GAME_EVENT, to=room_id)


@event_on("debug")
def sio_debug(sid):
    return {"rooms": sio.rooms(sid)}
