#!/bin/ash

python manage.py makemigrations ai
python manage.py migrate ai
python manage.py migrate --fake
gunicorn -w ${WEBSOCKET_WORKER} --threads ${WEBSOCKET_THREAD} -b 0.0.0.0:${GAMEAI_PORT} game_ai.wsgi