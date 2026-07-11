from typing import Any, Dict, List
from django.shortcuts import render

from gameapp.decorators import api_post

from rest_framework.request import Request

from gameapp.wsgi_utils import make_rooms


# Create your views here.
@api_post
def make_rooms_post(req: Request, data: Dict[str, Any]):
    room_name: str = data["room_name"]
    user_id: List[int] = data["user_id"]

    try:
        make_rooms(room_name, user_id)
    except Exception as e:
        print(f"Exception {e}")
        raise e
