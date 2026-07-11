from typing import List

from django.http import HttpRequest, HttpResponse
from rest_framework.decorators import parser_classes, api_view
from rest_framework.parsers import JSONParser
from rest_framework.request import Request

from authapp.envs import JWT_URL
from authapp.requests import post
from exceptions.CustomException import BadRequestException, UnauthenticatedException


def api_endpoint(http_method_names: List[str]):
    def _func(func):
        func = api_view(http_method_names)(func)
        func = parser_classes([JSONParser])(func)
        return func

    return _func


def examine_data(func):
    def wrapper(req: Request, *args, **kwargs):
        if not isinstance(req.data, dict):
            raise BadRequestException()
        return func(req, data=req.data, *args, **kwargs)

    return wrapper


def api_post(func):
    func = examine_data(func)
    func = api_endpoint(["POST"])(func)

    return func


def api_delete(func):
    return api_endpoint(["DELETE"])(func)


def api_get(func):
    return api_endpoint(["GET"])(func)


def authenticated(skip_2fa=False):
    def _func(func):
        def wrapper(req: HttpRequest, *args, **kwargs):
            if "Authorization" not in req.headers:
                raise UnauthenticatedException()

            authorization_header: str = req.headers["Authorization"]
            if not authorization_header.startswith("Bearer "):
                raise UnauthenticatedException()

            jwt = authorization_header[7:]
            res = post(f"{JWT_URL}/jwt/check", json={"jwt": jwt, "skip_2fa": skip_2fa})
            if not res.ok:
                return HttpResponse(res.content, status=res.status_code)

            res = res.json()
            return func(req, user_id=int(res["user_id"]), *args, *kwargs)

        return wrapper

    return _func
