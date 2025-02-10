import enum
import json
from logging import Logger
import threading
import requests
from typing import TYPE_CHECKING


from gameapp.envs import USER_URL
from gameapp.sio import GAME_OVER_EVENT, sio_disconnect, sio_emit, sio_enter_room
from gameapp.models import (
    TempMatch,
    TempMatchRoom,
    TempMatchRoomUser,
    TempMatchUser,
    User,
)
from gameapp.utils import get_match_name, now


from .process import MatchProcess
from .timeout import WaitingProcess
from .matchuser import MatchUser
from .matchdict import match_dict


if TYPE_CHECKING:
    from .matchdict import MatchDict


logger = Logger(__name__)


class MatchStage(enum.Enum):
    NOT_STARTED = 0
    WAITING = 1
    MATCH = 2
    FINISHED = 3


class Match:
    def __init__(self, match: TempMatch) -> None:
        self.stage = MatchStage.NOT_STARTED
        self.match = match
        self.room_name = get_match_name(match)

        self.users: list[MatchUser] = []
        self.online: list[bool] = []

        self.match_process = MatchProcess(match, self)
        self.waiting_process = WaitingProcess(self)

        self.lock = threading.Lock()

    def __set_stage_waiting(self):
        self.stage = MatchStage.WAITING
        self.waiting_process.start()

    def __get_user_idx(self, user: MatchUser) -> int:
        for i, u in enumerate(self.users):
            if u["id"] == user["id"]:
                return i
        return -1

    def __get_other_user(self, user: MatchUser) -> MatchUser | None:
        if user["id"] == self.users[0]["id"]:
            return self.users[1]
        elif user["id"] == self.users[1]["id"]:
            return self.users[0]
        else:
            return None

    def __set_win_and_lose(
        self,
        winner: MatchUser,
        loser: MatchUser,
    ):
        self.stage = MatchStage.FINISHED

        self.__set_win(winner, loser)
        self.__set_lose(loser)
        sio_disconnect(loser["sid"])

    def __set_lose(self, loser: MatchUser):
        TempMatchRoomUser.objects.filter(
            user_id=loser["id"], temp_match_room_id=self.match.match_room.id
        ).delete()
        self.stage = MatchStage.FINISHED

    def __set_win(self, winner: MatchUser, loser: MatchUser):
        winner_user = User.objects.get(id=winner["id"])
        self.match.winner = winner_user
        end_at = now()
        self.match.end_at = end_at
        self.match.save()
        print("winner match: ", self.match.winner_match)
        json_obj = {
            "player1_id": winner["id"],
            "player1_score": get_score(winner["id"], self.match.id),
            "player2_id": loser["id"],
            "player2_score": get_score(loser["id"], self.match.id),
            "winner_id": winner["id"],
            "match_date": (
                self.match.start_at if self.match.start_at is not None else end_at
            ).isoformat(),
            "play_time": (
                (end_at - self.match.start_at).total_seconds()
                if self.match.start_at is not None
                else 0
            ),
        }
        winner_idx = self.__get_user_idx(winner)
        game_over_data = {
            "winner": "paddle1" if winner_idx == 0 else "paddle2",
            "paddle1": (
                json_obj["player1_score"]
                if winner_idx == 0
                else json_obj["player2_score"]
            ),
            "paddle2": (
                json_obj["player2_score"]
                if winner_idx == 0
                else json_obj["player1_score"]
            ),
        }

        print(f"emit {GAME_OVER_EVENT} = {json.dumps(game_over_data)}")
        sio_emit(
            GAME_OVER_EVENT,
            game_over_data,
            self.room_name,
        )
        try:
            print(f"Post to user url, _internal/dashboard, data={json.dumps(json_obj)}")
            requests.post(
                f"{USER_URL}/_internal/dashboard",
                json=json_obj,
            )
        except Exception as e:
            print("error:", e)
        if self.match.winner_match is not None:
            print("winner match id: ", self.match.winner_match.id)
            TempMatchUser.objects.create(
                user_id=winner["id"],
                temp_match_id=self.match.winner_match.id,
            )
            match_decided(match_dict, winner, self.match.winner_match)
        else:
            print(f"deleting winner id = {winner['id']}")
            TempMatchRoomUser.objects.filter(user_id=winner["id"]).delete()

            # Dependency on CASCADE
            print(f"Deleting match room name ={self.match.match_room.room_name}")
            TempMatchRoom.objects.filter(
                room_name=self.match.match_room.room_name
            ).delete()

        match_dict.delete_match_id(self.match.id)
        self.stage = MatchStage.FINISHED

    def user_decided(self, user: MatchUser) -> bool:
        with self.lock:
            print(f"user={user} is decided to be in {self.room_name}")
            if len(self.users) >= 2:
                return False
            self.users.append(user)
            self.online.append(False)
            self.match_process.user_decided(user)

        if len(self.users) == 2 and self.online[0]:
            self.__set_stage_waiting()

        return True

    def user_connected(self, user: MatchUser) -> bool:
        with self.lock:
            print(f"user={user} is connected to {self.room_name}")
            idx = self.__get_user_idx(user)
            if idx == -1:
                return False
            if self.online[idx]:
                return True

            sio_emit(
                "init",
                {"paddleId": "paddle1" if idx == 0 else "paddle2"},
                to=user["sid"],
            )
            sio_enter_room(user["sid"], self.room_name)

            self.users[idx]["sid"] = user["sid"]
            self.users[idx]["name"] = user["name"]
            self.online[idx] = True
            if self.stage == MatchStage.FINISHED:
                # Other user has exited
                self.__set_win(self.users[idx], self.users[1 - idx])
                return True
            elif len(self.online) != 1:
                if not self.online[0] or not self.online[1]:
                    self.__set_stage_waiting()
                else:
                    self.waiting_process.stop()
                    self.match_process.start()
                    self.stage = MatchStage.MATCH
        return True

    def timed_out(self):
        print("Match - timed out")
        with self.lock:
            if self.stage != MatchStage.WAITING:
                return
            if self.online[0] and self.online[1]:
                return

            if self.online[0]:
                self.__set_win_and_lose(self.users[0], self.users[1])
            else:
                self.__set_win_and_lose(self.users[1], self.users[0])

    def user_disconnected(self, user: MatchUser):
        with self.lock:
            if (
                self.stage == MatchStage.NOT_STARTED
                or self.stage == MatchStage.FINISHED
            ):
                return
            elif self.stage == MatchStage.WAITING:
                idx = self.__get_user_idx(user)
                if idx == -1:
                    return

                if self.online[idx]:
                    self.waiting_process.stop()
                    self.__set_lose(user)
            elif self.stage == MatchStage.MATCH:
                winner = self.__get_other_user(user)
                if winner is None:
                    return
                self.__set_win_and_lose(winner, user)

    def __get_user_idx_with_name(self, name: str) -> int | None:
        for i, u in enumerate(self.users):
            if u["name"] == name:
                return i
        return None

    def alert_winner(self, winner_name: str):
        with self.lock:
            idx = self.__get_user_idx_with_name(winner_name)
            if idx is None:
                return

            winner = self.users[idx]
            loser = self.__get_other_user(winner)
            if loser is None:
                return

            self.__set_win_and_lose(winner, loser)


def match_decided(match_dict: "MatchDict", user: MatchUser, match: TempMatch):
    room_id = match.id
    if room_id not in match_dict.get_dict():
        match_dict[room_id] = Match(match)

    match_dict[room_id].user_decided(user)


def get_score(user_id: int, match_id: int):
    temp_match_user = TempMatchUser.objects.get(user_id=user_id, temp_match_id=match_id)
    return temp_match_user.score
