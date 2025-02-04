#!/bin/ash

python manage.py makemigrations jwtapp
python manage.py migrate
python manage.py runserver 0.0.0.0:${JWT_PORT}
