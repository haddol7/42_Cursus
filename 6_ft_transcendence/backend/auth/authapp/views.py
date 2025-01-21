import os
import urllib.parse
import urllib.request
from django.http import HttpRequest, HttpResponse, HttpResponseRedirect
from django.shortcuts import render
import requests
import urllib

from exceptions.CustomException import BadRequestFieldException, InternalException
from rest_framework.request import Request

# Create your views here.


def get_os_str(key: str) -> str:
    val: str | None = os.getenv(key)
    if val is None:
        raise InternalException()
    return val


def get_os_int(key: str) -> int:
    return int(get_os_str(key))


OAUTH_42_URL = get_os_str("OAUTH_42_URL")
OAUTH_TOKEN_URL = get_os_str("OAUTH_TOKEN_URL")
OAUTH_CLIENT_ID = get_os_str("OAUTH_CLIENT_ID")
OAUTH_CLIENT_SECRET = get_os_str("OAUTH_CLIENT_SECRET")

JWT_URL = get_os_str("JWT_URL")


def get_42_oauth(req: Request):
    redirect_to = req.GET.get("redirectTo")
    if redirect_to is None:
        raise BadRequestFieldException("redirectTo")
    redirect_to = urllib.parse.quote(redirect_to)

    # TODO: fix state to cache storage
    state = "complex_state"
    return HttpResponseRedirect(
        f"{OAUTH_42_URL}?"
        + f"client_id={OAUTH_CLIENT_ID}"
        + f"&redirect_uri={redirect_to}"
        + f"&response_type=code&state={state}"
    )


def get_42_code(req: HttpRequest):
    code = req.GET.get("code")
    state = req.GET.get("state")
    if code is None:
        raise BadRequestFieldException("code")
    elif state is None:
        raise BadRequestFieldException("state")

    # ensure state is state
    res = requests.post(
        OAUTH_TOKEN_URL,
        data={
            "grant_type": "authorization_code",
            "client_id": OAUTH_CLIENT_ID,
            "client_secret": OAUTH_CLIENT_SECRET,
            "redirect_uri": "http://localhost:8000/api",
            "code": code,
            "state": state,
        },
    )
    print(res.ok)
    print(res.content)
    return HttpResponse()


def refresh_token(req: HttpRequest):
    refresh_token = req.POST.get("refreshToken")
    if refresh_token is None:
        raise BadRequestFieldException("refreshToken")
    res = requests.post(f"{JWT_URL}/jwt/refresh", data={"refresh_token": refresh_token})
    if not res.ok:
        return HttpResponse(res.content, status=res.status_code)
    print(res.content)
    return HttpResponse("OK!")
