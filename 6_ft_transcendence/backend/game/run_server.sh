#!/bin/ash

python manage.py makemigrations gameapp
python manage.py migrate gameapp
python manage.py migrate --fake
python manage.py flush --no-input
gunicorn -w ${WEBSOCKET_WORKER} --threads ${WEBSOCKET_THREAD} -b 0.0.0.0:${GAME_PORT} game.wsgi