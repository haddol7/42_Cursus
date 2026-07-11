#!/bin/ash

python manage.py makemigrations twofaapp
python manage.py migrate twofaapp
python manage.py migrate --fake
python manage.py runserver 0.0.0.0:${TWOFA_PORT}