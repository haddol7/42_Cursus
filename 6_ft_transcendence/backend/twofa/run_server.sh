#!/bin/ash

python manage.py makemigrations twofaapp
python manage.py migrate 
python manage.py runserver 0.0.0.0:${TWOFA_PORT}