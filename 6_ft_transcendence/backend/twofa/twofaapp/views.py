import pyotp
from django.shortcuts import render
from django.http import HttpRequest, HttpResponseNotAllowed, JsonResponse
from logging import Logger
from rest_framework.request import Request
from typing import Any, Dict


from exceptions.CustomException import (
    BadRequestFieldException,
    TwoFARegisterException,
    TwoFARequiredException,
)

from twofaapp.decorators import api_delete, api_get, api_post
from twofaapp.envs import OTP_ISSUER
from twofaapp.utils import get_int, get_str, get_userinfo_or_none, set_totp_secret

# Create your views here.

logger = Logger(__name__)


@api_get
def get_info(req: Request):
    user_id = get_int(req.query_params, "user_id")

    user_info = get_userinfo_or_none(user_id)
    if user_info is None:
        raise TwoFARegisterException()

    return JsonResponse({"twofa_name": user_info.twofa_name})


@api_post
def post_info(req: Request, data: Dict[str, Any]):
    user_id = get_int(data, "user_id")
    logger.info(f"userid = {user_id}")

    name = get_str(data, "name")

    if type(name) != str:
        raise BadRequestFieldException("name")

    secret = pyotp.random_base32()
    set_totp_secret(user_id, secret, name)
    url = pyotp.totp.TOTP(secret).provisioning_uri(name=name, issuer_name=OTP_ISSUER)

    return JsonResponse({"url": url})


def handle_info(req: HttpRequest):
    if req.method == "GET":
        return get_info(req)
    elif req.method == "POST":
        return post_info(req)
    else:
        return HttpResponseNotAllowed(["GET", "POST"])


@api_post
def post_code(req: Request, data: Dict[str, Any]):
    user_id = get_int(data, "user_id")
    code = get_str(data, "code")

    user_info = get_userinfo_or_none(user_id)
    if user_info is None:
        raise TwoFARegisterException()

    if "skip" not in data or data["skip"] == False:
        totp_secret = user_info.twofa_secret
        totp_now = pyotp.TOTP(totp_secret).now()
        if totp_now != code:
            raise BadRequestFieldException("code")

    user_info.twofa_passed = True
    user_info.save()

    return JsonResponse({})


@api_get
def get_check(req: Request):
    user_id = get_int(req.query_params, "user_id")

    user_info = get_userinfo_or_none(user_id)
    if user_info is None:
        raise TwoFARegisterException()

    if not user_info.twofa_passed:
        raise TwoFARequiredException()

    return JsonResponse({})


@api_delete
def delete_check(req: Request):
    user_id = get_int(req.query_params, "user_id")

    user_info = get_userinfo_or_none(user_id)
    if user_info is None:
        raise TwoFARegisterException()

    user_info.twofa_passed = False
    user_info.save()

    return JsonResponse({})


def handle_check(req: HttpRequest):
    if req.method == "GET":
        return get_check(req)
    elif req.method == "DELETE":
        return delete_check(req)
    else:
        return HttpResponseNotAllowed(["GET", "DELETE"])
