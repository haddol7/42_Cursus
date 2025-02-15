from http.client import INTERNAL_SERVER_ERROR
from logging import Logger
from django.http import JsonResponse
import socketio
import socketio.exceptions

from exceptions.CustomException import CustomException
from websocket.sio import sio


logger = Logger(__name__)


def event_on(event: str, *args, **kwargs):
    def handle_exception(func):
        def _wrapper(*args, **kwargs):
            try:
                ret = func(*args, **kwargs)
                if ret is None:
                    return JsonResponse({})
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

        _outer = sio.on(event, *args, **kwargs)(_wrapper)  # type: ignore
        return _outer

    return handle_exception
