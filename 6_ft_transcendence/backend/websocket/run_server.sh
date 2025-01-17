#!/bin/ash

python manage.py migrate
# python manage.py runserver 0.0.0.0:7600
gunicorn -w ${WEBSOCKET_WORKER} --threads ${WEBSOCKET_THREAD} -b 0.0.0.0:7600 websocket.wsgi
