import enum
import random
import threading
from typing import Any, List, Tuple, TypedDict
from gameapp.sio import sio
from gameapp.models import (
    TempMatch,
    TempMatchRoom,
    TempMatchRoomUser,
    TempMatchUser,
    User,
)
from socketio.exceptions import ConnectionRefusedError

from django.db.models import Subquery


NAMESPACE = "/game"
TIMEOUT_SEC = 10

GAME_BOUNDS = {"x": 5, "y": 7}
PADDLE_WIDTH = 1
PADDLE_HEIGHT = 0.2
BALL_RADIUS = 0.2
WINNING_SCORE = 2
BALL_SIZE = {"x": 0.4, "y": 0.4, "z": 0.4}


def _get_from_sess(sid: str) -> Tuple[int, str]:
    with sio.session(sid, namespace=NAMESPACE) as sess:
        user_id: int = sess["user_id"]
        user_name: str = sess["user_name"]

    return user_id, user_name


class MatchUser(TypedDict):
    id: int
    name: str
    sid: str


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

    def __set_win_and_lose(self, winner: MatchUser, loser: MatchUser):
        self.stage = MatchStage.FINISHED
        sio.emit("gameOver", {"winner": winner["name"]}, namespace=NAMESPACE)

        self.__set_win(winner)

        self.__set_lose(loser)
        sio.disconnect(loser["sid"], namespace=NAMESPACE)

    def __set_lose(self, loser: MatchUser):
        TempMatchRoomUser.objects.filter(
            user_id=loser["id"], temp_match_room_id=self.match.match_room.id
        ).delete()
        self.stage = MatchStage.FINISHED

    def __set_win(self, winner: MatchUser):
        winner_user = User.objects.get(id=winner["id"])
        self.match.winner = winner_user
        self.match.save()
        print("winner match: ", self.match.winner_match)
        if self.match.winner_match is not None:
            print("winner match id: ", self.match.winner_match.id)
            TempMatchUser.objects.create(
                user_id=winner["id"],
                temp_match_id=self.match.winner_match.id,
            )
            match_decided(winner, self.match.winner_match)
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
            self.users[idx]["sid"] = user["sid"]
            self.online[idx] = True
            if len(self.online) != 1:
                if not self.online[0] or not self.online[1]:
                    self.__set_stage_waiting()
                else:
                    self.waiting_process.stop()
                    self.match_process.start()
                    self.stage = MatchStage.MATCH
        sio.enter_room(user["sid"], room=self.room_name, namespace=NAMESPACE)
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

    def __get_user_idx_with_name(self, name: str):
        for i, u in enumerate(self.users):
            if u["name"] == name:
                return i
        return -1

    def alert_winner(self, winner_name: str):
        with self.lock:
            idx = self.__get_user_idx_with_name(winner_name)
            if idx == -1:
                return

            winner = self.users[idx]
            loser = self.__get_other_user(winner)
            if loser is None:
                return

            self.__set_win_and_lose(winner, loser)


match_dict_2: dict[int, Match] = {}


def clear_match_dict():
    global match_dict_2
    match_dict_2 = {}


class MatchProcess(threading.Thread):
    def __init__(self, match: TempMatch, match_manager: Match):
        super().__init__()
        self.match_manager = match_manager
        self.room_name = get_match_name(match)
        self.users: list[MatchUser] = []
        self.ball = {"x": 0.0, "y": 0.0, "vx": 0.1, "vy": 0.1}
        self.score = [0, 0]

        # Protected by lock
        self.paddle = [0.0, 0.0]
        self.game_over = False

        self.event = threading.Event()
        self.lock = threading.Lock()

    def user_decided(self, user: MatchUser):
        self.users.append(user)

    def set_paddle(self, user_id: int, x: float):
        idx = -1
        if user_id == self.users[0]["id"]:
            idx = 0
        elif user_id == self.users[1]["id"]:
            idx = 1
        else:
            # TODO: throw error
            return

        x = max(
            -GAME_BOUNDS["x"] + PADDLE_WIDTH / 2,
            min(GAME_BOUNDS["x"] - PADDLE_WIDTH / 2, x),
        )

        with self.lock:
            self.paddle[idx] = x

    def reset_game(self, scorer: str):
        self.ball = {"x": 0.0, "y": 0.0, "vx": 0.0, "vy": 0.0}

        paddle = [0.0, 0.0]
        with self.lock:
            self.paddle = paddle[:]

        sio.emit(
            "resetPositions",
            {"ball": self.ball, "paddles": paddle},
            to=self.room_name,
            namespace="/game",
        )

        def start_game_func():
            initial_speed = 0.05
            self.ball["vx"] = initial_speed * (
                (int(random.random() * 10000) % 2) * 2 - 1
            )
            self.ball["vy"] = (
                initial_speed if scorer == self.users[0]["name"] else -initial_speed
            )
            sio.emit("updateBall", self.ball, to=self.room_name, namespace="/game")

        t = threading.Timer(3.0, start_game_func)
        t.start()

    def run(self):
        if len(self.users) != 2:
            return
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

            if ball["y"] >= GAME_BOUNDS["y"] - BALL_SIZE["y"] / 2:
                score[0] += 1
                sio.emit("updateScore", score, to=self.room_name, namespace=NAMESPACE)
                self.reset_game(self.users[0]["name"])
            elif ball["y"] <= -GAME_BOUNDS["y"] + BALL_SIZE["y"] / 2:
                score[1] += 1
                sio.emit("updateScore", score, to=self.room_name, namespace=NAMESPACE)
                self.reset_game(self.users[1]["name"])

            elif score[0] == WINNING_SCORE or score[1] == WINNING_SCORE:
                self.game_over = True
                winner = (
                    self.users[0]["name"]
                    if score[0] == WINNING_SCORE
                    else self.users[1]["name"]
                )
                self.event.set()
                self.match_manager.alert_winner(winner)
            else:
                sio.emit("updateBall", ball, to=self.room_name, namespace="/game")

            self.event.wait(0.016)

    def stop(self):
        self.event.set()


class WaitingProcess(threading.Thread):
    def __init__(self, match: Match):
        super().__init__()
        self.event = threading.Event()
        self.time_out = False
        self.match = match

    def run(self):
        print("WatingProcess - Run start")
        self.event.wait(TIMEOUT_SEC)
        if self.event.is_set():
            return
        self.time_out = True
        self.event.set()
        self.match.timed_out()

    def stop(self):
        print("WaitingProcess - Run Stopped")
        self.event.set()

    def is_time_out(self) -> bool:
        if not self.event.is_set():
            return False
        return self.time_out


def get_match_name(match: TempMatch):
    return f"{match.match_room.room_name}_{match.id}"


def on_connect(sid, auth):
    print(f"connected sid={sid}")

    # TODO: auth with JWT
    user_id = int(auth["user_id"])
    username = auth["user_name"]

    with sio.session(sid, namespace=NAMESPACE) as sess:
        sess["user_id"] = user_id
        sess["user_name"] = username

    room_user = get_room_user_or_none(user_id)
    if room_user is None or room_user.is_online:
        raise ConnectionRefusedError("temp match room user none or online")
    room_user.is_online = True
    room_user.save()
    print(room_user)

    # room_name = room_user.temp_match_room.room_name
    # sio.enter_room(sid, room_name, namespace=NAMESPACE)

    match_user = get_match_user_or_none(user_id)
    if match_user is None:
        raise ConnectionRefusedError("temp match user none")
    print(match_user)

    join_match(sid, match_user, username=username)


def get_match_user_or_none(user_id: int):
    try:
        temp_user = TempMatchUser.objects.get(user_id=user_id)
    except:
        temp_user = None
    return temp_user


def on_disconnect(sid, reason):
    # TODO: If reason is CLIENT_DISCONNECT, wait to be reconnected

    with sio.session(sid, namespace=NAMESPACE) as sess:
        user_id: int = sess["user_id"]

    match_user = get_match_user_or_none(user_id)
    if match_user:
        match_id = match_user.temp_match.id
        user = MatchUser(id=match_user.user.id, name=match_user.user.username, sid=sid)
        match_dict_2[match_id].user_disconnected(user)
        print(f"setting lose for user_id={user_id}")
    else:
        print("disconnecting... but match_user not found")


def get_room_user_or_none(user_id: int):
    try:
        temp_match_room_user = TempMatchRoomUser.objects.get(user_id=user_id)
    except:
        temp_match_room_user = None
    return temp_match_room_user


def match_decided(user: MatchUser, match: TempMatch):
    room_id = match.id
    if room_id not in match_dict_2:
        match_dict_2[room_id] = Match(match)

    match_dict_2[room_id].user_decided(user)


def join_match(sid: str, match_user: TempMatchUser, username: str):
    room_id = match_user.temp_match.id
    if room_id not in match_dict_2:
        match_dict_2[room_id] = Match(match_user.temp_match)

    user = MatchUser(id=match_user.user.id, name=username, sid=sid)
    match_dict_2[room_id].user_connected(user)


def clear_room(room_name: str):
    temp_room = TempMatchRoom.objects.get(room_name=room_name)
    room_user = TempMatchRoomUser.objects.filter(temp_match_room_id=temp_room.id)
    room_user.delete()

    temp_match = TempMatch.objects.filter(match_room_id=temp_room.id)
    temp_match_user = TempMatchUser.objects.filter(temp_match__in=temp_match)

    temp_match_user.delete()
    temp_match.delete()

    temp_room.delete()


def assign_kv(target: dict[Any, Any], source: dict[Any, Any]):
    for k, v in source.items():
        target[k] = v


def on_paddle_move(sid: str, data):
    print(f"paddle_move event received! sid={sid}, data={data}")


def on_next_game(sid: str):
    user_id, username = _get_from_sess(sid)
    print(f"next_game: sid={sid}, user_id={user_id}")

    from django.db.models import Min

    user_min_match = TempMatch.objects.filter(tempmatchuser__user_id=user_id).aggregate(
        round=Min("round")
    )["round"]

    match_user = TempMatchUser.objects.filter(
        user_id=user_id, temp_match__round=user_min_match
    ).get()

    print(match_user)
    print("next match id = ", match_user.temp_match.id)

    join_match(sid, match_user, username)


def init_matches(users: List[TempMatchUser]):
    for u in users:
        match_id = u.temp_match.id
        if match_id not in match_dict_2:
            match_dict_2[match_id] = Match(u.temp_match)

        user = MatchUser(id=u.user.id, name=u.user.username, sid="")
        print(user)
        match_dict_2[match_id].user_decided(user)
