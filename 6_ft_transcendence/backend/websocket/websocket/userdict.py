import logging
import threading
from typing import Dict

from exceptions.CustomException import InternalException
from websocket.roomuser import RoomUser


class UserDict:
    logger = logging.getLogger(__name__)

    def __init__(self) -> None:
        self.lock = threading.Lock()
        self.dict: Dict[int, RoomUser] = {}

    def add(self, user_id: int, roomuser: RoomUser):
        with self.lock:
            if user_id in self.dict:
                return False
            self.dict[user_id] = roomuser
            return True

    def remove(self, user_id: int):
        with self.lock:
            if user_id not in self.dict:
                self.logger.info(f"user_id={user_id} is not in dict! not deleting")
                return False
            self.logger.info(f"user_id{user_id} is in dict! deleting the user")
            del self.dict[user_id]
            return True

    def get(self, user_id: int) -> RoomUser:
        with self.lock:
            if user_id not in self.dict:
                self.logger.error(f"Trying to find user_id={user_id} failed!")
                raise InternalException()
            return self.dict[user_id]
