import random
import threading
import logging
from typing import TYPE_CHECKING

from exceptions.CustomException import InternalException
from gameapp.sio import (
    GAME_OVER_EVENT,
    RESET_POSITIONS_EVENT,
    UPDATE_BALL_EVENT,
    UPDATE_PADDLE_EVENT,
    UPDATE_SCORE_EVENT,
    sio_emit,
)
from gameapp.models import TempMatch, TempMatchUser
from gameapp.utils import get_match_name, now

from .matchuser import MatchUser

if TYPE_CHECKING:
    from .match import Match


GAME_BOUNDS = {"x": 5, "y": 7}
PADDLE_WIDTH = 1
PADDLE_HEIGHT = 0.2
BALL_RADIUS = 0.2
WINNING_SCORE = 2
PADDLE_MOVE = 0.075
INITIAL_SPEED = 0.05
BALL_SIZE = {"x": 0.4, "y": 0.4, "z": 0.4}

GAME_RIGHTEND = GAME_BOUNDS["x"] - PADDLE_WIDTH / 2


class MatchProcess(threading.Thread):
    logger = logging.getLogger(__name__)

    def __init__(
        self,
        match: TempMatch,
        is_with_ai: bool,
        match_manager: "Match",
        users: list[MatchUser],
    ):
        super().__init__()

        self.is_with_ai = is_with_ai
        self.match_manager = match_manager
        self.room_name = get_match_name(match)
        self.users: list[MatchUser] = users

        if len(self.users) != 2:
            self.logger.error(f"users len is not 2, users={users}")
            raise InternalException()

        self.ball = {"x": 0.0, "y": 0.0, "vx": 0.1, "vy": 0.1}
        self.score = [0, 0]
        self.match = match

        # Protected by lock
        self.paddle = [0.0, 0.0]
        self.game_over = False

        self.event = threading.Event()
        self.lock = threading.Lock()

    def __get_idx(self, user_id: int):
        if self.users[0]["id"] == user_id:
            return 0
        if self.users[1]["id"] == user_id:
            return 1
        return -1

    def set_paddle(self, user_id: int, paddle_direction: float):
        with self.lock:
            self.logger.info(
                f"user_id={user_id}, room_name={self.room_name}, direction={paddle_direction}"
            )
            idx = self.__get_idx(user_id)

        self.logger.info(
            f"user_id={user_id}, idx={idx}, paddle_direction={paddle_direction}"
        )
        if paddle_direction == 0:
            self.logger.info(f"user_id={user_id}, paddle_direction is zero, returning")
            return

        with self.lock:
            paddle_pos = self.paddle[idx]

        normalized_direction = PADDLE_MOVE if paddle_direction > 0 else -PADDLE_MOVE
        self.logger.info(
            f"user_id={user_id} paddle_pos was={paddle_pos} normalized_direction={normalized_direction}"
        )
        x = paddle_pos + normalized_direction
        x = max(-GAME_RIGHTEND, min(GAME_RIGHTEND, x))
        self.logger.info(f"user_id={user_id}, prev val={paddle_pos}, become x={x}")

        with self.lock:
            self.paddle[idx] = x

        emit_json = {"paddleId": "paddle1" if idx == 0 else "paddle2", "position": x}
        self.logger.info(f"user_id={user_id}, emitting event={UPDATE_PADDLE_EVENT}")
        sio_emit(
            UPDATE_PADDLE_EVENT,
            emit_json,
            self.room_name,
        )

    def reset_game(self, scorer_idx: int):
        self.ball = {"x": 0.0, "y": 0.0, "vx": 0.0, "vy": 0.0}

        paddle = [0.0, 0.0]
        with self.lock:
            self.paddle = paddle[:]
        sio_emit(RESET_POSITIONS_EVENT, {}, self.room_name)

        def start_game_func():
            initial_speed = INITIAL_SPEED
            self.ball["vx"] = initial_speed * (
                (int(random.random() * 10000) % 2) * 2 - 1
            )
            if self.is_with_ai:
                self.ball["vy"] = initial_speed if scorer_idx == 0 else -initial_speed
            else:
                self.ball["vy"] = -initial_speed
            self.logger.info(f"reset_game send event {UPDATE_BALL_EVENT}")
            sio_emit(UPDATE_BALL_EVENT, self.ball, self.room_name)

        t = threading.Timer(3.0, start_game_func)
        t.start()

    def __is_not_decided(self):
        if not self.is_with_ai and len(self.users) != 2:
            return True
        return False

    def __start_hook(self):
        self.match.start_at = now()
        self.match.save()

    def __move_ball(self):
        ball = self.ball
        ball["x"] += ball["vx"]
        ball["y"] += ball["vy"]

    def __check_ball_hit_wall(self):
        ball = self.ball
        if (
            ball["x"] >= GAME_BOUNDS["x"] - BALL_SIZE["x"] / 2
            or ball["x"] <= -GAME_BOUNDS["x"] + BALL_SIZE["x"] / 2
        ):
            ball["vx"] *= -1
            if ball["x"] > 0:
                ball["x"] = GAME_BOUNDS["x"] - BALL_SIZE["x"] / 2
            else:
                ball["x"] = -GAME_BOUNDS["x"] + BALL_SIZE["x"] / 2

    def __check_ball_hit_paddle(self, paddle: list[float]):
        ball = self.ball
        hit_bottom_paddle = (
            ball["y"] - BALL_SIZE["y"] / 2 <= -GAME_BOUNDS["y"] + PADDLE_HEIGHT
            and ball["x"] + BALL_SIZE["x"] / 2 >= paddle[0] - PADDLE_WIDTH / 2
            and ball["x"] - BALL_SIZE["x"] / 2 <= paddle[0] + PADDLE_WIDTH / 2
        )

        hit_top_paddle = (
            ball["y"] + BALL_SIZE["y"] / 2 >= GAME_BOUNDS["y"] - PADDLE_HEIGHT
            and ball["x"] + BALL_SIZE["x"] / 2 >= paddle[1] - PADDLE_WIDTH / 2
            and ball["x"] - BALL_SIZE["x"] / 2 <= paddle[1] + PADDLE_WIDTH / 2
        )

        if hit_bottom_paddle or hit_top_paddle:
            ball["vy"] *= -1.05
            ball["vx"] *= 1.05

            ball["vy"] = min(ball["vy"], 0.2)
            ball["vy"] = max(ball["vy"], -0.2)

    def __check_scorer(self):
        ball = self.ball
        score = self.score

        scorer = -1
        if ball["y"] >= GAME_BOUNDS["y"] - BALL_SIZE["y"] / 2:
            scorer = 0
        elif ball["y"] <= -GAME_BOUNDS["y"] + BALL_SIZE["y"] / 2:
            scorer = 1

        if scorer != -1:
            score[scorer] += 1
            self.logger.info(f"match process emit event={UPDATE_SCORE_EVENT}")
            sio_emit(
                UPDATE_SCORE_EVENT,
                {"paddle1": score[0], "paddle2": score[1]},
                self.room_name,
            )

            self.reset_game(scorer)

    def __is_winner(self) -> bool:
        if self.is_with_ai:
            return False
        return self.score[0] == WINNING_SCORE or self.score[1] == WINNING_SCORE

    def __finish_match(self):
        with self.lock:
            if self.event.is_set():
                return
            self.game_over = True
            self.event.set()

        score = self.score
        winner_idx = 0 if score[0] == WINNING_SCORE else 1
        winner = self.users[winner_idx]["name"]  # type: ignore

        sio_emit(
            GAME_OVER_EVENT,
            {
                "winner": "paddle1" if winner_idx == 0 else "paddle2",
                "paddle1": self.score[0],
                "paddle2": self.score[1],
            },
            self.room_name,
        )
        set_score(self.users[0]["id"], self.match.id, self.score[0])
        set_score(self.users[1]["id"], self.match.id, self.score[1])
        self.match_manager.alert_winner(winner)

    def is_event_set(self):
        with self.lock:
            return self.event.is_set()

    def get_scores(self):
        with self.lock:
            return self.score[:]

    def run(self):
        with self.lock:
            if self.__is_not_decided():
                return
        self.__start_hook()

        while not self.is_event_set():
            with self.lock:
                paddle = self.paddle[:]
                game_over = self.game_over

            if game_over:
                break

            self.__move_ball()
            self.__check_ball_hit_wall()
            self.__check_ball_hit_paddle(paddle)
            self.__check_scorer()

            if self.__is_winner():
                self.__finish_match()
            else:
                sio_emit(UPDATE_BALL_EVENT, self.ball, self.room_name)

            self.event.wait(0.016)

    def stop(self):
        with self.lock:
            self.event.set()


def set_score(user_id: int, match_id: int, score: int):
    user = TempMatchUser.objects.get(user_id=user_id, temp_match_id=match_id)
    user.score = score
    user.save()
