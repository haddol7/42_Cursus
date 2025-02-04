from typing import Any

from django.http import HttpResponse

from exceptions.CustomException import CustomException, InternalException


class ExceptionMiddleware:
    def __init__(self, get_response) -> None:
        self.get_response = get_response

    def __call__(self, request) -> Any:
        print(f"middleware start {request.method} {request.path}")
        response = self.get_response(request)
        print("middleware end")
        return response

    def process_exception(self, request, exception: Exception):
        if isinstance(exception, CustomException):
            print("custom exception", exception, "trace=", exception.__traceback__)
            return HttpResponse(exception.__str__(), status=exception.get_status_code())
        print("not custom exception", exception, "type=", type(exception), "trace=", exception.__traceback__)
        return HttpResponse(InternalException().__str__(), status=500)
