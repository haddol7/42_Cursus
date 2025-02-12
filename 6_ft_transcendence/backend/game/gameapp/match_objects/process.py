import random
import threading
from typing import TYPE_CHECKING


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
BALL_SIZE = {"x": 0.4, "y": 0.4, "z": 0.4}


class MatchProcess(threading.Thread):
    def __init__(self, match: TempMatch, match_manager: "Match", is_with_ai: bool):
        super().__init__()
        self.is_with_ai = is_with_ai
        self.match_manager = match_manager
        self.room_name = get_match_name(match)
        self.users: list[MatchUser] = []
        self.ball = {"x": 0.0, "y": 0.0, "vx": 0.1, "vy": 0.1}
        self.score = [0, 0]
        self.match = match

        # Protected by lock
        self.paddle = [0.0, 0.0]
        self.game_over = False

        self.event = threading.Event()
        self.lock = threading.Lock()

    def user_decided(self, user: MatchUser):
        self.users.append(user)

    def set_paddle(self, user_id: int, paddle_direction: float):
        idx = -1
        if user_id == self.users[0]["id"]:
            idx = 0
        elif user_id == self.users[1]["id"]:
            idx = 1
        else:
            # TODO: throw error
            return

        if paddle_direction == 0:
            return

        with self.lock:
            paddle_pos = self.paddle[idx]
        normalized_direction = (paddle_direction * 0.075) / abs(paddle_direction)
        x = paddle_pos + normalized_direction
        x = max(
            -GAME_BOUNDS["x"] + PADDLE_WIDTH / 2,
            min(GAME_BOUNDS["x"] - PADDLE_WIDTH / 2, x),
        )

        with self.lock:
            self.paddle[idx] = x

        sio_emit(
            UPDATE_PADDLE_EVENT,
            {"paddleId": "paddle1" if idx == 0 else "paddle2", "positiion": x},
            self.room_name,
        )

    def reset_game(self, scorer_idx: int):
        self.ball = {"x": 0.0, "y": 0.0, "vx": 0.0, "vy": 0.0}

        paddle = [0.0, 0.0]
        with self.lock:
            self.paddle = paddle[:]

        sio_emit(RESET_POSITIONS_EVENT, {}, self.room_name)

        def start_game_func():
            initial_speed = 0.05
            self.ball["vx"] = initial_speed * (
                (int(random.random() * 10000) % 2) * 2 - 1
            )
            self.ball["vy"] = initial_speed if scorer_idx == 0 else -initial_speed
            sio_emit(UPDATE_BALL_EVENT, self.ball, self.room_name)

        t = threading.Timer(3.0, start_game_func)
        t.start()

    def run(self):
        if not self.is_with_ai and len(self.users) != 2:
            return
        self.match.start_at = now()
        self.match.save()
        while not self.event.is_set():
            ball = self.ball
            score = self.score

            with self.lock:
                paddle = self.paddle[:]
                game_over: bool = self.game_over

            if game_over:
                break

            ball["x"] += ball["vx"]
            ball["y"] += ball["vy"]

            if (
                ball["x"] >= GAME_BOUNDS["x"] - BALL_SIZE["x"] / 2
                or ball["x"] <= -GAME_BOUNDS["x"] + BALL_SIZE["x"] / 2
            ):
                ball["vx"] *= -1
                if ball["x"] > 0:
                    ball["x"] = GAME_BOUNDS["x"] - BALL_SIZE["x"] / 2
                else:
                    ball["x"] = -GAME_BOUNDS["x"] + BALL_SIZE["x"] / 2

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
                ball["vy"] *= -1.1

            scorer = -1
            if ball["y"] >= GAME_BOUNDS["y"] - BALL_SIZE["y"] / 2:
                scorer = 0
            elif ball["y"] <= -GAME_BOUNDS["y"] + BALL_SIZE["y"] / 2:
                scorer = 1

            if scorer != -1:
                score[scorer] += 1
                sio_emit(
                    UPDATE_SCORE_EVENT,
                    {"paddle1": score[0], "paddle2": score[1]},
                    self.room_name,
                )

                self.reset_game(scorer)

            if not self.is_with_ai and (
                score[0] == WINNING_SCORE or score[1] == WINNING_SCORE
            ):
                winner_idx = 0 if score[0] == WINNING_SCORE else 1

                with self.lock:
                    self.game_over = True

                winner = (
                    self.users[0]["name"]
                    if score[0] == WINNING_SCORE
                    else self.users[1]["name"]
                )
                self.event.set()
                sio_emit(
                    GAME_OVER_EVENT,
                    {
                        "winner": "paddle1" if winner_idx == 0 else "paddle2",
                        "paddle1": self.score[0],
                        "paddle2": self.score[1],
                    },
                    self.room_name,
                )
                set_score(
                    self.users[winner_idx]["id"], self.match.id, self.score[winner_idx]
                )
                set_score(
                    self.users[1 - winner_idx]["id"],
                    self.match.id,
                    self.score[1 - winner_idx],
                )
                self.match_manager.alert_winner(winner)
            else:
                sio_emit(UPDATE_BALL_EVENT, ball, self.room_name)

            self.event.wait(0.016)

    def stop(self):
        self.event.set()


def set_score(user_id: int, match_id: int, score: int):
    user = TempMatchUser.objects.get(user_id=user_id, temp_match_id=match_id)
    user.score = score
    user.save()
