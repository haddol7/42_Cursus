from typing import List
from rest_framework.decorators import parser_classes, api_view

from rest_framework.parsers import JSONParser


def api_endpoint(http_method_names: List[str]):
    def _func(func):
        func = parser_classes([JSONParser])(func)
        func = api_view(http_method_names)(func)
        return func

    return _func


def api_post(func):
    _func = api_endpoint(["POST"])
    return _func(func)
