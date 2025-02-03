from http.client import INTERNAL_SERVER_ERROR
import socketio
import socketio.exceptions
from exceptions.CustomException import CustomException
from gameapp.sio import sio

print(f"decorators sioid=${id(sio)}")


def event_on(event: str, *args, **kwargs):
    def handle_exception(func):
        def _wrapper(*args, **kwargs):
            try:
                ret = func(*args, **kwargs)
                print(f"ret = {ret}")
                if ret is None:
                    return {}
                else:
                    return ret
            except socketio.exceptions.ConnectionRefusedError as e:
                print(f"error1={e}")
                raise e
            except CustomException as e:
                print(f"error2={e}")
                return {"error": e.__str__(), "code": e.get_status_code()}
            except Exception as e:
                print("ERROR: ", e)
                return {"error": e, "code": INTERNAL_SERVER_ERROR}

        _outer = sio.on(event, *args, **kwargs)(_wrapper)  # type: ignore
        return _outer

    return handle_exception
