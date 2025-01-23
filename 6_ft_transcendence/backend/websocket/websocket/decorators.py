from xmlrpc.client import INTERNAL_ERROR

import socketio
import socketio.exceptions
from exceptions.CustomException import CustomException
from websocket.wsgi import sio


def event_on(event: str):
    def handle_exception(func):
        def _wrapper(*args, **kwargs):
            try:
                ret = func(*args, **kwargs)
                if ret is None:
                    return {}
                else:
                    return ret
            except socketio.exceptions.ConnectionRefusedError as e:
                raise e
            except CustomException as e:
                return {"error": e.__str__(), "code": e.get_status_code()}
            except Exception as e:
                print("ERROR: ", e)
                return {"error": e, "code": INTERNAL_ERROR}

        _outer = sio.on(event)(_wrapper)  # type: ignore
        return _outer

    return handle_exception
