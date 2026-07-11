import enum
import logging
import threading
from typing import TYPE_CHECKING

from exceptions.CustomException import InternalException
from gameapp.envs import USER_URL
from gameapp.models import (
    TempMatch,
    TempMatchRoom,
    TempMatchRoomUser,
    TempMatchUser,
)
from gameapp.requests import post
from gameapp.sio import (
    GAME_OVER_EVENT,
    INIT_EVENT,
    OPPONENT_EVENT,
    sio_disconnect,
    sio_emit,
    sio_enter_room,
)
from gameapp.utils import get_match_name, now
from .matchdict import match_dict
from .matchuser import AI_ID, AiUser, MatchUser, RealUser
from .process import MatchProcess
from .timeout import WaitingProcess

if TYPE_CHECKING:
    from .matchdict import MatchDict


class MatchStage(enum.Enum):
    NOT_STARTED = 0
    WAITING = 1
    MATCH = 2
    FINISHED = 3


class Match:
    logger = logging.getLogger(__name__)

    def __init__(self, match: TempMatch, is_with_ai: bool = False) -> None:
        self.stage = MatchStage.NOT_STARTED
        self.match = match
        self.room_name = get_match_name(match)
        self.is_with_ai = is_with_ai

        self.users: list[MatchUser] = []
        self.online: list[bool] = []

        self.match_process: MatchProcess | None = None
        self.waiting_process = WaitingProcess(self)

        self.listeners: list[Match] = []
        self.opponent = "unknown vs. unknown"

        self.lock = threading.Lock()

    def emit_opponent_on_listen(self, opponent_name: str):
        self.opponent = opponent_name
        self.emit_opponent()

    def emit_opponent(self):
        sio_emit(
            OPPONENT_EVENT,
            {"opponent": self.opponent, "lastGame": False},
            self.room_name,
        )

    def emit_final_opponent(self):
        sio_emit(
            OPPONENT_EVENT,
            {"opponent": self.opponent, "lastGame": True},
            self.room_name,
        )

    def add_listener(self, sibling: "Match"):
        self.logger.debug(
            f"listener len = {len(self.listeners)}, listener = {[mat.room_name for mat in self.listeners]}"
        )
        self.listeners.append(sibling)

    def __set_stage_waiting(self):
        self.stage = MatchStage.WAITING
        self.waiting_process.start()

    def __set_stage_match(self):
        self.stage = MatchStage.MATCH
        self.match_process = MatchProcess(self.match, self.is_with_ai, self, self.users)
        self.match_process.start()

    def __get_user_idx(self, user: MatchUser) -> int:
        for i, u in enumerate(self.users):
            if u["id"] == user["id"]:
                return i
        return -1

    def __set_win_and_lose(self, winner_idx: int):
        """
        Caller should have been able to mark this stage as `FINISHED`.
        Only one caller who could mark this `stage` as `FINISHED` can execute this method.

        This method is called only when the match is finished successfully.
        It should do the following work:
        - mark the `loser` to be loser in this match.
            - Delete the user in the room user.
            - Disconnect the user (`__set_lose()` does not handle this)
        - mark the `winner` to be winner in this match.
            - Register the user to the next game if it exists.
            - Set the winner as the final winner and disconnect the user if next game does not exist.
        - Save the match result in the database
        """

        loser_idx = 1 - winner_idx
        self.logger.info(
            f"set win and lose: winner_idx={winner_idx}, loser_idx={loser_idx}"
        )
        self.__set_win(winner_idx)
        self.__set_lose(loser_idx)
        sio_disconnect(self.users[loser_idx]["sid"])

    def __set_lose(self, loser_idx: int):
        """
        Caller should have been able to mark this stage as `FINISHED`.
        Only one caller who could mark this `stage` as `FINISHED` can execute this method.

        `loser` lost in this match. The state of `winner` is unknown.
        `loser` will be deleted in the list of room user.
        `stage` is changed to `FINISHED`.

        `loser` is not disconnected, because `loser` can be already disconnected.

        Possible situation to call this method is one of the following:
        - User disconnected before the game, while in the game.
        - Opponent got the winning score.

        If the first situation happens, only this method is called.
        If the second situation happens, `__set_win_and_lose()` method is called,
            which results in calling this method.
        """
        TempMatchRoomUser.objects.filter(
            user_id=self.users[loser_idx]["id"],
            temp_match_room_id=self.match.match_room.id,
        ).delete()
        self.stage = MatchStage.FINISHED

    def __set_win(self, winner_idx: int):
        """
        If the stage is `FINISHED`, but the `winner` is not received event certainly, it is okay to call this method, but only one time.

        Mark `winner_idx` user to be the winner. This happens when one of the following happens:
            - Opponent was disconnected before this user is connected.
            - Opponent was disconnected in the match.
            - User reached the WINNING_SCORE first.

        When the above condition is met, the match result will be stored in the Database.
        Winner will be propagated to the next match (if the match exists), and the user can emit "nextGame" event, which will take the user to the next game.
        If no such match exists, the user will be the final winner and will be disconnected.
        Also, this match is marked as FINISHED.

        If the user is connected, this method is happening right after the condition is met.

        If the user is not connected, this method is happening when the user is connected.

        If the user gives up even when the condition is satisfied, this method will not be called.
        In this case, this match is ignored and other matches have to know this situation.
        """

        end_at = now()
        winner = self.users[winner_idx]
        loser = self.users[1 - winner_idx]
        self.logger.info(f"winner match: {self.match.winner_match}")

        scores = (
            self.match_process.get_scores()
            if self.match_process is not None
            else [0, 0]
        )

        json_obj = {
            "player1_id": self.users[0]["id"],
            "player1_score": scores[0],
            "player2_id": self.users[1]["id"],
            "player2_score": scores[1],
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

        game_over_data = {
            "winner": "paddle1" if winner_idx == 0 else "paddle2",
            "paddle1": scores[0],
            "paddle2": scores[1],
        }

        sio_emit(GAME_OVER_EVENT, game_over_data, self.room_name)

        resp = post(
            f"{USER_URL}/_internal/dashboard",
            json=json_obj,
        )
        if not resp.ok:
            self.logger.error(f"resp is not ok, resp = {resp.text}")

        if self.match.winner_match is not None:
            self.logger.info(f"winner match id: {self.match.winner_match.id}")
            TempMatchUser.objects.create(
                user_id=winner["id"],
                temp_match_id=self.match.winner_match.id,
            )
            match_decided(match_dict, winner, self.match.winner_match)  # type: ignore
        else:
            self.logger.info(f"deleting winner id = {winner['id']}")
            TempMatchRoomUser.objects.filter(user_id=winner["id"]).delete()

            # Dependency on CASCADE
            self.logger.info(
                f"Deleting match room name ={self.match.match_room.room_name}"
            )
            TempMatchRoom.objects.filter(
                room_name=self.match.match_room.room_name
            ).delete()

            self.emit_final_opponent()

            self.logger.info(f"winner={winner} is disconnected")
            sio_disconnect(winner["sid"])

        self.emit_opponent()

        for listener in self.listeners:
            if "name" in winner:
                listener.emit_opponent_on_listen(winner["name"])

        match_dict.delete_match_id(self.match.id)
        self.stage = MatchStage.FINISHED

    def get_match_name(self):
        with self.lock:
            if len(self.users) == 0:
                return "unknown vs. unknown"
            elif len(self.users) == 1:
                if "name" in self.users[0]:
                    return f"{self.users[0]['name']} vs. unknown"
                else:
                    raise InternalException()
            else:
                if len(self.users) != 2:
                    self.logger.error(
                        f"users len expected 2, but got {len(self.users)}"
                    )
                    raise InternalException()

                if self.is_with_ai:
                    assert "name" in self.users[0]
                    return f"{self.users[0]['name']} vs. AI"
                else:
                    assert "name" in self.users[0] and "name" in self.users[1]
                    return f"{self.users[0]['name']} vs. {self.users[1]['name']}"

    def user_decided(self, user: RealUser) -> bool:
        with self.lock:
            self.logger.info(f"user={user} is decided to be in {self.room_name}")
            if len(self.users) >= 2:
                self.logger.info(
                    f"user={user} could not be in {self.room_name}, because there already exists users={self.users}"
                )
                return False

            self.users.append(user)
            self.online.append(False)

            if len(self.users) == 2 and self.online[0]:
                self.__set_stage_waiting()
        for listener in self.listeners:
            listener.emit_opponent_on_listen(self.get_match_name())
        return True

    def user_connected(self, user: RealUser) -> bool:
        self.logger.info(f"user={user} is connected to {self.room_name}")
        with self.lock:
            idx = self.__get_user_idx(user)
            if idx == -1:
                self.logger.error(
                    f"user={user} is connected, but the user is not found"
                )
                return False
            if self.online[idx]:
                self.logger.error(
                    f"user={user} is connected, but the user is already connected"
                )
                return True

            sio_emit(
                INIT_EVENT,
                {"paddleId": "paddle1" if idx == 0 else "paddle2"},
                to=user["sid"],
            )
            sio_enter_room(user["sid"], self.room_name)
            self.users[idx] = user
            self.online[idx] = True

            if self.stage == MatchStage.FINISHED:
                self.logger.info(
                    f"user={user} is connected, but the stage is marked as FINISHED, so the user wins automatically"
                )
                self.__set_win(idx)
                return True

            if len(self.online) == 2:
                if not self.online[0] or not self.online[1]:
                    self.__set_stage_waiting()
                else:
                    self.waiting_process.stop()
                    self.__set_stage_match()
        return True

    def is_user_connected(self, user_id: int) -> bool:
        with self.lock:
            for idx, user in enumerate(self.users):
                if user["id"] == user_id and self.online[idx]:
                    return True
        return False

    def is_user_dto_connected(self, user_dto: "MatchUser") -> bool:
        with self.lock:
            for idx, user in enumerate(self.users):
                if user["id"] == user_dto["id"] and user["sid"] == user_dto["sid"]:
                    return True
        return False

    def ai_connected(self, sid: str):
        self.logger.info(f"ai is connected! self.room_name={self.room_name}")
        self.logger.info(f"When AI is connected, users len={len(self.users)}")
        if len(self.users) != 1:
            self.logger.error(
                f"When AI is connected, self.users len is not 1! users={self.users}"
            )

        self.users.append(AiUser(is_ai=True, sid=sid, id=AI_ID))
        self.online.append(True)

        with self.lock:
            sio_emit(INIT_EVENT, {"paddleId": "paddle2"}, to=sid)
            sio_enter_room(sid, self.room_name)

            self.logger.info("waiting process stop")
            self.waiting_process.stop()
            self.logger.info("match process start")
            self.__set_stage_match()

    def timed_out(self):
        self.logger.info("Match - timed out")
        with self.lock:
            if self.stage != MatchStage.WAITING:
                return
            if len(self.users) != 2:
                self.logger.error(
                    f"stage is WAITING, but the len of users is not 2, self.users={self.users}"
                )
            if self.online[0] and self.online[1]:
                return

            self.stage = MatchStage.FINISHED
            winner_idx = 0 if self.online[0] else 1
            self.__set_win_and_lose(winner_idx)

    def __disconnect_with_ai(self, user: RealUser):
        self.logger.info(f"user={user} is disconnected, but match is with ai")

        if self.match_process is not None:
            self.match_process.stop()

        ai_sid = self.users[1]["sid"]
        sio_disconnect(ai_sid)

        TempMatchRoomUser.objects.filter(user_id=user["id"]).delete()
        TempMatchUser.objects.filter(user_id=user["id"]).delete()

    def user_disconnected(self, user: RealUser):
        with self.lock:
            if self.is_with_ai:
                return self.__disconnect_with_ai(user)
            self.logger.info(f"user={user} is disconnected, current stage={self.stage}")

            if (
                self.stage == MatchStage.NOT_STARTED
                or self.stage == MatchStage.FINISHED
            ):
                self.logger.error(f"self.stage={self.stage}, but user is disconnected!")
                return
            elif self.stage == MatchStage.WAITING:
                idx = self.__get_user_idx(user)
                if idx == -1:
                    self.logger.info(
                        f"user is disconnected, but user={user['id']} could not be found in match={self.room_name}"
                    )
                    return

                if self.online[idx]:
                    self.waiting_process.stop()
                    self.stage = MatchStage.FINISHED
                    self.__set_lose(idx)
            elif self.stage == MatchStage.MATCH:
                assert self.match_process is not None

                loser_idx = self.__get_user_idx(user)
                self.match_process.stop()
                self.stage = MatchStage.FINISHED
                self.__set_lose(loser_idx)
                self.__set_win(1 - loser_idx)

    def alert_winner(self, winner_idx: int):
        with self.lock:
            if self.stage == MatchStage.FINISHED:
                self.logger.info(
                    "self.stage is already FINISHED, returning `alert_winner`"
                )
                return

            self.logger.info(
                "self.stage is not FINISHED, setting FINISHED and set win and lose"
            )
            self.stage = MatchStage.FINISHED
            self.__set_win_and_lose(winner_idx)


def match_decided(match_dict: "MatchDict", user: RealUser, match: TempMatch):
    room_id = match.id
    if room_id not in match_dict.get_dict():
        match_dict[room_id] = Match(match)

    match_dict[room_id].user_decided(user)


def get_score(user_id: int, match_id: int):
    temp_match_user = TempMatchUser.objects.get(user_id=user_id, temp_match_id=match_id)
    return temp_match_user.score
