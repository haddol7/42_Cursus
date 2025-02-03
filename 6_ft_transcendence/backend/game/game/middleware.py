from typing import Any

from django.http import HttpResponse

from exceptions.CustomException import CustomException, InternalException


class ExceptionMiddleware:
    def __init__(self, get_response) -> None:
        self.get_response = get_response

    def __call__(self, request) -> Any:
        print("middlware start")
        response = self.get_response(request)
        print("middleware end")
        return response

    def process_exception(self, request, exception):
        if isinstance(exception, CustomException):
            print("Custom exceptioin = ", exception)
            return HttpResponse(exception.__str__(), status=exception.get_status_code())
        print("Not custom exception = ", exception, ", type=", type(exception))
        return HttpResponse(InternalException().__str__(), status=500)
