#!/bin/ash

python manage.py makemigrations gameapp
python manage.py migrate gameapp
# python manage.py runserver 0.0.0.0:7700
gunicorn -w ${WEBSOCKET_WORKER} --threads ${WEBSOCKET_THREAD} -b 0.0.0.0:7700 game.wsgi