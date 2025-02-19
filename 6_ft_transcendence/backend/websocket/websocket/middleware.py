import datetime
import logging
from datetime import timedelta
from django.http import HttpResponse
from typing import Any

from exceptions.CustomException import CustomException, InternalException


class ExceptionMiddleware:
    logger = logging.getLogger(__name__)

    def __init__(self, get_response) -> None:
        self.get_response = get_response

    def __call__(self, request) -> Any:
        start = datetime.datetime.now(datetime.timezone.utc)
        self.logger.info(f"middleware start {request.method} {request.path}")
        response = self.get_response(request)
        elapsed = datetime.datetime.now(datetime.timezone.utc) - start
        self.logger.info(
            f"middleware end, elapsed={elapsed / timedelta(milliseconds=1)}ms"
        )
        return response

    def process_exception(self, request, exception: Exception):
        if isinstance(exception, CustomException):
            self.logger.error(f"custom exception {type(exception)}")
            self.logger.exception(exception)
            return HttpResponse(exception.__str__(), status=exception.get_status_code())
        self.logger.error(f"not custom exception type= {type(exception)}")
        self.logger.exception(exception)
        return HttpResponse(InternalException().__str__(), status=500)
