import datetime
from django.forms import model_to_dict
from django.http import HttpRequest, HttpResponse, JsonResponse
from django.shortcuts import render

from exceptions.CustomException import BadRequestFieldException
from jwtapp.models import User
from jwtapp.utils import check_jwt, check_refresh_token, make_token_pair

# Create your views here.


def check_jwt_request(req: HttpRequest):
    jwt = req.POST.get("jwt")
    if jwt is None:
        raise BadRequestFieldException("jwt")
    check_jwt(jwt)
    return HttpResponse()


def refresh_jwt(req: HttpRequest):
    old_refresh = req.POST.get("refresh_token")
    if old_refresh is None:
        raise BadRequestFieldException("refresh_token")

    payload = check_refresh_token(old_refresh)
    access_token, refresh_token = make_token_pair(payload["user_id"])

    return JsonResponse({"access_token": access_token, "refresh_token": refresh_token})


def make_new_jwt(req: HttpRequest):
    user_id = req.POST.get("user_id")
    if user_id is None:
        raise BadRequestFieldException("user_id")

    access_token, refresh_token = make_token_pair(int(user_id))
    return JsonResponse({"access_token": access_token, "refresh_token": refresh_token})


def make_user(req: HttpRequest):
    user_obj = User.objects.create(
        username="asdf", profile_url="url", created_at=datetime.datetime.now()
    )
    user_obj.save()
    return JsonResponse(model_to_dict(user_obj))
