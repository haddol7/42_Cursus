"""
WSGI config for game project.

It exposes the WSGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/5.1/howto/deployment/wsgi/
"""

import os
from django.core.wsgi import get_wsgi_application
import socketio

from game.decorators import event_on
from gameapp.sio import sio
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


@sio.event(namespace="/game")
def connect(sid, environ, auth):
    on_connect(sid, auth)


@event_on("paddleMove", namespace="/game")
def paddle_move(sid, data):
    on_paddle_move(sid, data)


@event_on("nextGame", namespace="/game")
def next_game(sid):
    on_next_game(sid)


@sio.event(namespace="/game")
def disconnect(sid, reason):
    on_disconnect(sid, reason)
