"""
WSGI config for websocket project.

It exposes the WSGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/5.1/howto/deployment/wsgi/
"""

import os
import socketio

from django.core.wsgi import get_wsgi_application

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "websocket.settings")

application = get_wsgi_application()
sio = socketio.Server()
application = socketio.WSGIApp(sio, application)


sid_list = []


@sio.event
def connect(sid, environ, auth):
    print(sid, environ, auth)
    sio.enter_room(sid, "sio_room")
    sid_list.append(sid)


@sio.event
def disconnect(sid, reason):
    print(sid, reason)
    sio.leave_room(sid, "sio_room")
    sid_list.remove(sid)


@sio.event
def send_msg(sid, data):
    print(sid, data)
    sio.emit("broadcast_msg", data, room="sio_room")


@sio.event
def sio_event(sid, data):
    print(sid, data)
    return "hello!!"
