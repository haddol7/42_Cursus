#!/bin/ash

python manage.py makemigrations
python manage.py migrate
gunicorn -w ${WEBSOCKET_WORKER} --threads ${WEBSOCKET_THREAD} -b 0.0.0.0:${WS_PORT} websocket.wsgi
