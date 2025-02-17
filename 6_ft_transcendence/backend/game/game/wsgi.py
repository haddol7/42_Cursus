"""
WSGI config for game project.

It exposes the WSGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/5.1/howto/deployment/wsgi/
"""

import os
from django.core.wsgi import get_wsgi_application
import socketio
import socketio.exceptions

from exceptions.CustomException import CustomException, InternalException
from game.decorators import event_on
from gameapp.sio import NAMESPACE, sio
import django

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "game.settings")
django.setup()

from gameapp.wsgi_utils import (
    on_connect,
    on_disconnect,
    on_next_game,
    on_paddle_move,
)

application = get_wsgi_application()
application = socketio.WSGIApp(sio, application)


@sio.event(namespace=NAMESPACE)
def connect(sid, environ, auth):
    try:
        on_connect(sid, auth)
    except socketio.exceptions.ConnectionRefusedError as e:
        raise e
    except CustomException as e:
        print("Custom Exception = ", e)
        raise socketio.exceptions.ConnectionRefusedError(e.__str__())
    except Exception as e:
        print("Other exception: ", e)
        raise socketio.exceptions.ConnectionRefusedError(InternalException().__str__())


@event_on("paddleMove", namespace=NAMESPACE)
def paddle_move(sid, data):
    on_paddle_move(sid, data)


@event_on("nextGame", namespace=NAMESPACE)
def next_game(sid):
    on_next_game(sid)


@sio.event(namespace=NAMESPACE)
def disconnect(sid, reason):
    try:
        on_disconnect(sid, reason)
    except Exception as e:
        print("on disconnect, error=", e)
        raise e
