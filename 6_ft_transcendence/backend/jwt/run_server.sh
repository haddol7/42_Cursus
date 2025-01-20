#!/bin/ash

cp .my_pgpass ~/.my_pgpass
chmod 0600 ~/.my_pgpass

ls -al ~/.my_pgpass

cp .pg_service.conf ~/.pg_service.conf
python manage.py makemigrations
python manage.py migrate
python manage.py runserver 0.0.0.0:8100