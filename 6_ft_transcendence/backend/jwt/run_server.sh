#!/bin/ash

python manage.py makemigrations jwtapp
python manage.py migrate jwtapp
python manage.py runserver 0.0.0.0:8100
