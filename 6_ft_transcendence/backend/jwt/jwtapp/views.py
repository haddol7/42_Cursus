import datetime
from typing import Dict
from django.forms import model_to_dict
from django.http import HttpRequest, HttpResponse, JsonResponse
from django.shortcuts import render

from exceptions.CustomException import BadRequestException, BadRequestFieldException
from jwtapp.decorators import api_post
from jwtapp.models import User
from jwtapp.utils import check_jwt, check_refresh_token, make_token_pair

from rest_framework.request import Request

# Create your views here.


@api_post
def check_jwt_request(req: Request):
    if not isinstance(req.data, dict):
        print("req.data is not dict")
        raise BadRequestException()

    jwt = req.data["jwt"]
    if jwt is None:
        print("jwt is None")
        raise BadRequestFieldException("jwt")
    check_jwt(jwt)
    return HttpResponse()


@api_post
def refresh_jwt(req: Request):
    if not isinstance(req.data, dict):
        print("req.data is not dict")
        raise BadRequestException()

    old_refresh = req.data["refresh_token"]
    if old_refresh is None:
        raise BadRequestFieldException("refresh_token")

    payload = check_refresh_token(old_refresh)
    access_token, refresh_token = make_token_pair(payload["user_id"])

    return JsonResponse({"access_token": access_token, "refresh_token": refresh_token})


@api_post
def make_new_jwt(req: Request):
    if not isinstance(req.data, dict):
        print("req.data is not dict")
        raise BadRequestException()

    user_id = req.data["user_id"]
    if user_id is None:
        raise BadRequestFieldException("user_id")

    access_token, refresh_token = make_token_pair(int(user_id))
    return JsonResponse({"access_token": access_token, "refresh_token": refresh_token})


@api_post
def make_user(req: HttpRequest):
    user_obj = User.objects.create(
        username="asdf", profile_url="url", created_at=datetime.datetime.now()
    )
    user_obj.save()
    return JsonResponse(model_to_dict(user_obj))
