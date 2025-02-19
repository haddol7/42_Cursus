import logging
import threading
from typing import TYPE_CHECKING

from gameapp.connect_utils import connect_users, disconnect_users


if TYPE_CHECKING:
    from gameapp.match_objects.matchuser import RealUser


WAITING_SEC = 10


class WaitingUsersJoin(threading.Thread):
    def __init__(self, users: "list[RealUser]", room_name: str):
        super().__init__()
        self.event = threading.Event()
        self.users = users
        self.room_name = room_name

        self.lock = threading.Lock()
        self.ok = False

    def run(self):
        self.event.wait(WAITING_SEC)
        with self.lock:
            if not self.event.is_set():
                self.event.set()
                self.ok = False
            ok = self.ok

        if ok:
            connect_users(self.users)
        else:
            disconnect_users(self.room_name, self.users)
        waiting_dict.remove(self.room_name)

    def stop(self):
        with self.lock:
            if self.event.is_set():
                return
            self.event.set()
            self.ok = True

    def fail(self):
        with self.lock:
            if self.event.is_set():
                return False
            self.event.set()
            self.ok = False
            return True


class Waiting:
    logger = logging.getLogger(__name__)

    def __init__(self, users: "list[RealUser]", room_name: str) -> None:
        super().__init__()
        self.lock = threading.Lock()
        self.users = users
        self.isonline = [False for _ in self.users]
        self.online_cnt = 0

        self.waiting_join = WaitingUsersJoin(self.users, room_name)

    def __str__(self) -> str:
        return f"{self.users}, {self.online_cnt}/{len(self.users)}"

    def __find_user_idx(self, user_id: int) -> int | None:
        for i, u in enumerate(self.users):
            if u["id"] == user_id:
                return i
        self.logger.error(f"user_id={user_id} not found")
        return None

    def user_join(self, user: "RealUser"):
        with self.lock:
            user_idx = self.__find_user_idx(user["id"])
            if user_idx is None:
                return
            self.online_cnt += 1
            self.isonline[user_idx] = True
            self.users[user_idx] = user
            if self.online_cnt == 1:
                self.waiting_join.start()
            if self.online_cnt == len(self.users):
                self.waiting_join.stop()

    def user_disconnect(self, user: "RealUser"):
        with self.lock:
            return self.waiting_join.fail()


class WaitingDict:
    logger = logging.getLogger(__name__)

    def __init__(self):
        self.waiting_dict: dict[str, Waiting] = {}
        self.lock = threading.Lock()

    def add(self, room_name: str, waiting: Waiting):
        with self.lock:
            self.logger.info(
                f"room_name={room_name}, waiting={waiting.__str__()} is added"
            )
            self.waiting_dict[room_name] = waiting

    def get(self, room_name: str):
        with self.lock:
            if room_name not in self.waiting_dict:
                self.logger.info(
                    f"room_name={room_name} is not in dict! returning None"
                )
                return None
            self.logger.info(f"room_name={room_name} is found, returning the object")
            return self.waiting_dict[room_name]

    def remove(self, room_name: str):
        with self.lock:
            if room_name not in self.waiting_dict:
                self.logger.info(f"room_name={room_name} is not in dict, ignoring")
                return
            self.logger.info(f"room_name={room_name} is deleted!")
            del self.waiting_dict[room_name]


waiting_dict = WaitingDict()
