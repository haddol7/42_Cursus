from typing import Any
from django.http import HttpResponse, JsonResponse

import logging
import json
from rest_framework.request import Request

from ai.decorators import api_post
import socketio

from ai.requests import post
from ai.utils import get_int
from game_ai.envs import GAME_URL, JWT_URL

import neat
import pickle
import time
import numpy as np

# Create your views here.


NAMESPACE = "/game"


logger = logging.getLogger(__name__)


class AiClient:

    def sio_event(self, event_name: str):
        def _event(func):
            event_func = self.sio.on(event_name, namespace=NAMESPACE)
            return event_func(func)  # type: ignore

        return _event

    def sio_emit(self, event: str, data: dict[str, Any]):
        self.sio.emit(event, data, namespace=NAMESPACE)

    def ai_decide(self, network, paddle_x, ball_x, ball_y):
        output = network.activate((paddle_x, ball_x, ball_y))
        decision = np.argmax(output)
        return [-1, 0, 1][decision]

    def __init__(self, jwt: str) -> None:
        logger.info(f"AI client is created, jwt={jwt}")
        with open("ai/data/data.pkl", "rb") as f:
            best_genome = pickle.load(f)

        config_path = "ai/data/config-feedforward"
        config = neat.Config(
            neat.DefaultGenome,
            neat.DefaultReproduction,
            neat.DefaultSpeciesSet,
            neat.DefaultStagnation,
            config_path,
        )

        self.net = neat.nn.FeedForwardNetwork.create(best_genome, config)

        self.sio = socketio.Client(logger=True, engineio_logger=True)

        self.g_paddle_x = 0

        self.paddle_id = ""
        self.last_update_time = 0
        self.last_ball_data = None

        self.sio.connect(
            f"{GAME_URL}", namespaces=[NAMESPACE], auth={"ai": True, "jwt": jwt}
        )

        @self.sio_event("init")
        def init(data):
            logger.info("ai got init")
            self.paddle_id = data["paddleId"]

        @self.sio_event("updateBall")
        def updateBall(ball_data):
            logger.info(f"ai got updateBall, data={json.dumps(ball_data)}")
            if not self.sio.connected or self.paddle_id is None:
                return

            # 받아오는 데이터가 없을 때, 예측
            current_time = time.time()
            if current_time - self.last_update_time < 1.0:
                self.last_ball_data = self.predict_ball_position(self.last_ball_data)
            else:
                self.last_ball_data = ball_data
                self.last_update_time = current_time

            try:
                norm_x = self.last_ball_data["x"] / 2.5
                norm_y = self.last_ball_data["y"] / 3.5
                paddle_x = self.last_ball_data["AI_pos"]
                norm_paddle_x = paddle_x / 2.5

                move = self.ai_decide(self.net, norm_paddle_x, norm_x, norm_y)
                self.g_paddle_x = paddle_x + move * 0.075

                self.sio_emit(
                    "paddleMove",
                    {"paddleId": self.paddle_id, "paddleDirection": move},
                )

            except Exception as e:
                print(f"⚠️ AI 오류: {e}")

        @self.sio_event("hitPaddle")
        def hitPaddle(data):
            pass

        @self.sio_event("gameOver")
        def gameOver(data):
            logger.info("ai got gameover")
            self.sio.disconnect()

    def predict_ball_position(self, ball_data):
        ball_x = ball_data["x"]
        ball_y = ball_data["y"]
        vx = ball_data["vx"]
        vy = ball_data["vy"]

        predicted_x = ball_x + vx
        predicted_y = ball_y + vy
        if predicted_x >= 4.8 or predicted_x <= -4.8:
            vx = -vx
        elif predicted_y >= 6.6 or predicted_y <= -6.6:
            vy = -vy * 1.05
            vx = vx * 1.05

        if abs(vy) > 0.2:
            vy = 0.2 if vy > 0 else -0.2

        return {
            "x": predicted_x,
            "y": predicted_y,
            "vx": vx,
            "vy": vy,
            "AI_pos": self.g_paddle_x,
        }


client_list: list[AiClient] = []


@api_post
def post_ai(request: Request, data: dict[str, Any]):
    match_id = get_int(data, "match_id")
    resp = post(f"{JWT_URL}/jwt/token/ai", json={"match_id": match_id})
    if not resp.ok:
        return HttpResponse(resp.content, status=resp.status_code)

    jwt: str = resp.json()["access_token"]

    ai_client = AiClient(jwt)
    client_list.append(ai_client)

    logger.info(f"client list len = {len(client_list)}")

    return JsonResponse({})
