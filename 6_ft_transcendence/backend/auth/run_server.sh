#!/bin/ash

python manage.py makemigrations
python manage.py migrate

python manage.py runserver 0.0.0.0:${AUTH_PORT}
# gunicorn -w ${WEBSOCKET_WORKER} --threads ${WEBSOCKET_THREAD} -b 0.0.0.0:${AUTH_PORT} auth.wsgi