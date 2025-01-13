from django.shortcuts import render
from django.http import (
    HttpResponse,
    HttpResponseRedirect,
    HttpRequest,
    HttpResponseBadRequest,
    JsonResponse,
)
from django.db import InternalError
import requests
import os
import jwt
from datetime import timezone, datetime, timedelta
from exceptions.JWTCustomException import JWTExpired

import logging
import pyotp

# Create your views here.

logger = logging.getLogger(__name__)


def apiRedirected(request: HttpRequest):
    print("request:", request)
    code = request.GET.get("code")
    state = request.GET.get("state")
    print("code = ", code)
    print("state = ", state)
    if not code or not state:
        return HttpResponseBadRequest()
    res = requests.post(
        "https://api.intra.42.fr/oauth/token",
        data={
            "grant_type": "authorization_code",
            "client_id": os.getenv("CLIENT_ID"),
            "client_secret": os.getenv("CLIENT_SECRET"),
            "redirect_uri": "http://localhost:8000/api",
            "code": code,
            "state": state,
        },
    )
    print(res)
    print(res.ok)
    print(res.content)
    return HttpResponse("api Redirected!")


def loginTo42(request):
    print("loginTo42, request=", request)
    # TODO: fix state to random long string
    state = "long_unguessable"
    client_id = os.getenv("CLIENT_ID")
    if client_id is None:
        raise InternalError()

    return HttpResponseRedirect(
        "https://api.intra.42.fr/oauth/authorize?client_id="
        + client_id
        + "&redirect_uri=http%3A%2F%2Flocalhost%3A8000%2Fapi&response_type=code&state="
        + state
    )


def makeJWT(request):
    jwt_expire_seconds = os.getenv("JWT_EXPIRE_SECONDS")
    if jwt_expire_seconds is None:
        raise InternalError()
    jwt_expire_seconds = int(jwt_expire_seconds)
    payload = {
        "user_id": "mydecision",
        "exp": datetime.now(tz=timezone.utc) + timedelta(seconds=jwt_expire_seconds),
    }
    jwt_secret = os.getenv("JWT_SECRET")
    algorithm = os.getenv("JWT_ALGORITHM")
    encoded_jwt = jwt.encode(payload, jwt_secret, algorithm=algorithm)
    return HttpResponse(encoded_jwt)


def decodeJWT(request: HttpRequest):
    request_jwt = request.GET.get("jwt")
    jwt_secret = os.getenv("JWT_SECRET")
    jwt_algorithm = os.getenv("JWT_ALGORITHM")
    print("reuqest_jwt=", request_jwt)
    if request_jwt is None:
        return HttpResponseBadRequest()
    try:
        decoded_jwt = jwt.decode(
            jwt=request_jwt, key=jwt_secret, algorithms=jwt_algorithm
        )
        print(decoded_jwt)
        return JsonResponse(decoded_jwt)
    except Exception as e:
        logger.error(e)
        return JsonResponse({"message": JWTExpired().__format__()})


def helper(req: HttpRequest):
    secret = pyotp.random_base32()
    otp_secret = os.getenv("OTP_SECRET")
    if otp_secret is None:
        raise InternalError()

    url = pyotp.totp.TOTP(otp_secret).provisioning_uri(
        name="alice@google.com", issuer_name="Secure App"
    )

    return JsonResponse(
        {
            "hello": True,
            "pyotp_random_base32": secret,
            "otp_secret": otp_secret,
            "url": url,
        }
    )


def validate_totp(req: HttpRequest):
    otp_secret = os.getenv("OTP_SECRET")
    if otp_secret is None:
        raise InternalError()

    code = req.GET.get("code")
    if code is None:
        return HttpResponseBadRequest()

    totp = pyotp.TOTP(otp_secret)
    totp_now = totp.now()
    print("now = ", totp_now)
    result = totp_now == code
    return JsonResponse({"result": result})
