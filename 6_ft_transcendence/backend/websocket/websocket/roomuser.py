from typing import TypedDict


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
