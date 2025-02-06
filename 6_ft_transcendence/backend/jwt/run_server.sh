#!/bin/ash

python manage.py makemigrations jwtapp
python manage.py migrate jwtapp
python manage.py migrate --fake
python manage.py runserver 0.0.0.0:${JWT_PORT}
