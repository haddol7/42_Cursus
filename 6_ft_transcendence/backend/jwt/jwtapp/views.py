from typing import Any, Dict

from django.http import HttpRequest, HttpResponseNotAllowed, JsonResponse
from rest_framework.request import Request

from jwtapp.decorators import api_delete, api_get, api_post
from jwtapp.utils import (
    check_ai_token,
    check_jwt,
    check_refresh_token,
    delete_token_secret,
    get_ai_token,
    get_bool,
    get_int,
    get_str,
    is_user_online,
    make_token_pair,
)


# Create your views here.


@api_post
def check_jwt_request(req: Request, data: Dict[str, Any]):
    jwt: str = get_str(data, "jwt")
    skip_2fa: bool = get_bool(data, "skip_2fa")

    payload = check_jwt(jwt, skip_2fa)
    return JsonResponse({"user_id": payload["user_id"]})


@api_post
def refresh_jwt(req: Request, data: Dict[str, Any]):
    old_refresh = get_str(data, "refresh_token")

    payload = check_refresh_token(old_refresh)
    access_token, refresh_token, _ = make_token_pair(
        payload["user_id"], twofa_delete=False
    )

    return JsonResponse({"access_token": access_token, "refresh_token": refresh_token})


@api_post
def post_token(req: Request, data: Dict[str, Any]):
    user_id = get_int(data, "user_id")
    twofa_delete = get_bool(data, "twofa_delete")

    access_token, refresh_token, isnew = make_token_pair(
        user_id, twofa_delete=twofa_delete
    )
    return JsonResponse(
        {"access_token": access_token, "refresh_token": refresh_token, "isnew": isnew}
    )


@api_delete
def delete_token(req: Request):
    user_id = get_int(req.query_params, "user_id")

    delete_token_secret(user_id)
    return JsonResponse({})


def handle_token(req: HttpRequest):
    if req.method == "POST":
        return post_token(req)
    elif req.method == "DELETE":
        return delete_token(req)
    else:
        return HttpResponseNotAllowed(["POST", "DELETE"])


@api_get
def get_online(req: Request):
    user_id = get_int(req.query_params, "user_id")

    return JsonResponse({"isonline": is_user_online(user_id)})


@api_post
def post_token_ai(req: Request, data: dict[str, Any]):
    match_id = get_int(data, "match_id")
    access_token = get_ai_token(match_id)

    return JsonResponse({"access_token": access_token})


@api_post
def post_check_ai(req: Request, data: dict[str, Any]):
    jwt = get_str(data, "jwt")
    match_id = check_ai_token(jwt)

    return JsonResponse({"match_id": match_id})
