#!/bin/bash

apt-get update -y

python -m pip install --upgrade pip && \
python -m pip install -r /home/requirements.txt

cd /server

python manage.py makemigrations user
python manage.py migrate user
python manage.py runserver 0.0.0.0:11111