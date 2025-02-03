import datetime
import urllib.parse
import urllib.request
from django.http import (
    HttpRequest,
    HttpResponse,
    HttpResponseNotAllowed,
    HttpResponseRedirect,
    JsonResponse,
)
from django.shortcuts import render
import pyotp
import requests
import urllib

from authapp.decorators import (
    api_delete,
    api_endpoint,
    api_get,
    api_post,
    authenticated,
)
from authapp.envs import (
    JWT_URL,
    OAUTH_42_URL,
    OAUTH_CLIENT_ID,
    OAUTH_CLIENT_SECRET,
    OAUTH_TOKEN_URL,
    OTP_ISSUER,
)
from authapp.models import User
from authapp.utils import (
    delete_jwt_secrets,
    get_totp_secret,
    set_totp_secret,
    update_2fa_passed,
)
from exceptions.CustomException import (
    BadRequestFieldException,
    UnauthenticatedException,
)
from rest_framework.request import Request

# Create your views here.


APPLICATION_JSON = "application/json"


@api_get
def get_42_oauth(req: Request):
    redirect_to = req.GET.get("redirectTo")
    if redirect_to is None:
        raise BadRequestFieldException("redirectTo")
    redirect_to = urllib.parse.quote(redirect_to)

    return HttpResponseRedirect(
        f"{OAUTH_42_URL}?"
        + f"client_id={OAUTH_CLIENT_ID}"
        + f"&redirect_uri={redirect_to}"
        + "&response_type=code"
    )


@api_get
def get_42_code(req: HttpRequest):
    code = req.GET.get("code")
    if code is None:
        raise BadRequestFieldException("code")

    # ensure state is state
    res = requests.post(
        OAUTH_TOKEN_URL,
        data={
            "grant_type": "authorization_code",
            "client_id": OAUTH_CLIENT_ID,
            "client_secret": OAUTH_CLIENT_SECRET,
            "redirect_uri": "http://localhost:8200/auth/42/code",
            "code": code,
        },
    )

    print(res.ok)
    print(res.content)
    if not res.ok:
        raise UnauthenticatedException()
    # Access token, Refresh Token, scope, created_at, secret_valid_until

    # TODO: set username appropriately
    user = User.objects.create(
        username="username",
        profile_url="None",
        created_at=datetime.datetime.now(datetime.timezone.utc),
    )

    resp = requests.post(f"{JWT_URL}/jwt/new", json={"user_id": user.id})
    if not resp.ok:
        return JsonResponse(resp.json(), status=resp.status_code)

    return JsonResponse(resp.json())


@api_post
def refresh_token(req: Request, data: dict[str, str]):
    if "refreshToken" not in data:
        raise BadRequestFieldException("refreshToken")
    refresh_token = data["refreshToken"]
    if refresh_token is None:
        raise BadRequestFieldException("refreshToken")
    res = requests.post(f"{JWT_URL}/jwt/refresh", json={"refresh_token": refresh_token})
    if not res.ok:
        return JsonResponse(res.text, status=res.status_code)
    return HttpResponse()


def handle_2fa(req: HttpRequest):
    if req.method == "GET":
        return get_2fa(req)
    elif req.method == "POST":
        return post_2fa(req)
    else:
        return HttpResponseNotAllowed(["GET", "POST"])


@authenticated(skip_2fa=True)
@api_get
def get_2fa(req: Request, user_id: int):
    print("userid = ", user_id)

    if "name" not in req.query_params:
        raise BadRequestFieldException("name")

    name = req.query_params["name"]
    if type(name) != str:
        raise BadRequestFieldException("name")

    secret = pyotp.random_base32()
    set_totp_secret(user_id, secret, name)
    url = pyotp.totp.TOTP(secret).provisioning_uri(name=name, issuer_name=OTP_ISSUER)

    return JsonResponse({"url": url})


@authenticated(skip_2fa=True)
@api_post
def post_2fa(req: Request, user_id: int, data: dict[str, str]):
    print("post 2fa, user_id=", user_id)
    if "code" not in data:
        raise BadRequestFieldException("code")

    code = data["code"]
    totp_secret = get_totp_secret(user_id)
    totp_now = pyotp.TOTP(totp_secret).now()
    if totp_now != code:
        raise BadRequestFieldException("code")
    update_2fa_passed(user_id)
    return HttpResponse()


@authenticated()
@api_delete
def logout(req: Request, user_id: int):
    delete_jwt_secrets(user_id)
    return HttpResponse()
