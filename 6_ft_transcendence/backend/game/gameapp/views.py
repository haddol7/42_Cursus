from typing import Any, Dict, List, TypedDict
from django.http import HttpRequest, HttpResponseNotAllowed, JsonResponse
from django.shortcuts import render

from rest_framework.request import Request

from exceptions.CustomException import BadRequestFieldException
from gameapp.wsgi_utils import clear_match_dict, clear_room
from gameapp.decorators import api_delete, api_post
from gameapp.utils import get_int, get_list, get_str, make_rooms


# Create your views here.


class UserNameDto(TypedDict):
    user_id: int
    user_name: str


# Will make rooms for received info
# Will not allow when multiple user is in the game -> user.already_join_game
@api_post
def make_game(req: Request, data: Dict[str, Any]):
    room_name = get_str(data, "room_name")
    users = get_list(data, "users")
    print(users)
    users_list: List[UserNameDto] = []
    for u in users:
        if not isinstance(u, dict):
            raise BadRequestFieldException("users")
        user_id = get_int(u, "user_id")
        user_name = get_str(u, "user_name")
        users_list.append(UserNameDto(user_id=user_id, user_name=user_name))

    user_id_list: List[int] = [u["user_id"] for u in users_list]

    make_rooms(room_name, user_id_list)
    return JsonResponse({})


@api_delete
def delete_game(req: Request):
    room_name = get_str(req.query_params, "room_name")
    clear_room(room_name)
    clear_match_dict()
    return JsonResponse({})


def handle_game(req: HttpRequest):
    if req.method == "POST":
        return make_game(req)
    elif req.method == "DELETE":
        return delete_game(req)
    else:
        return HttpResponseNotAllowed(["POST", "DELETE"])
