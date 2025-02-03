#!/bin/ash

python manage.py makemigrations authapp
python manage.py migrate authapp
python manage.py runserver 0.0.0.0:8200