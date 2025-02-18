import datetime
import logging
import socketio
import socketio.exceptions
from datetime import timedelta
from django.http import JsonResponse
from http.client import INTERNAL_SERVER_ERROR

from exceptions.CustomException import CustomException
from .sio import sio

logger = logging.getLogger(__name__)


def event_on(event: str, *args, **kwargs):
    def handle_exception(func):
        def _wrapper(*args, **kwargs):
            start = datetime.datetime.now(datetime.timezone.utc)
            try:
                logger.debug(f"This websocket is for event={event}")
                ret = func(*args, **kwargs)
                if ret is None:
                    return {}
                return ret
            except socketio.exceptions.ConnectionRefusedError as e:
                logger.error("connection refused error")
                logger.exception(e)
                raise e
            except CustomException as e:
                logger.error(f"custom exception type={type(e)}")
                logger.exception(e)
                return {"error": e.__str__(), "code": e.get_status_code()}
            except Exception as e:
                logger.error(f"Unknown exception, type={type(e)}")
                logger.exception(e)
                return {"error": "internal_error", "code": INTERNAL_SERVER_ERROR}
            finally:
                elapsed = datetime.datetime.now(datetime.timezone.utc) - start
                logger.debug(f"Elapsed = {elapsed / timedelta(milliseconds=1)}ms")

        _outer = sio.on(event, *args, **kwargs)(_wrapper)  # type: ignore
        return _outer

    return handle_exception
