from typing import Any
from django.http import JsonResponse
from django.shortcuts import render

import requests
from rest_framework.request import Request

from ai.decorators import api_post
import socketio

from ai.utils import get_int
from game_ai.envs import GAME_URL, JWT_URL

# Create your views here.

sio_list: list[socketio.SimpleClient] = []


@api_post
def post_ai(request: Request, data: dict[str, Any]):
    match_id = get_int(data, "match_id")
    resp = requests.post(f"{JWT_URL}/jwt/token/ai", json={"match_id": match_id})
    jwt: str = resp.json()["access_token"]

    sio = socketio.SimpleClient()
    sio.connect(f"{GAME_URL}", namespace="/game", auth={"ai": True, "jwt": jwt})

    sio_list.append(sio)

    alive_cnt = 0
    for _sio in sio_list:
        alive_cnt += 1 if _sio.connected else 0

    print(f"sio connected? sid={sio.sid}, connected cnt = {alive_cnt}")

    return JsonResponse({})
