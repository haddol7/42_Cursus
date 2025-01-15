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


@sio.event
def connect(sid, environ, auth):
    print(sid, environ, auth)


@sio.event
def sio_event(sid, data):
    print(sid, data)
    return "hello!!"
