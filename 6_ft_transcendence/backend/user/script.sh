#!/bin/bash

apt-get update -y &&  \
apt-get install vim -y && \
apt-get install lsof && \ 
apt-get install net-tools -y && \
apt-get install postgresql -y && \
apt-get install curl -y

if [ -d "/server" ]; then 
    echo "/server already present, skipping creation"
else
    echo "/server not found, creating..."
    mkdir -p /server && chmod -R 755 /server
fi

python -m pip install --upgrade pip && \
python -m pip install -r /home/requirements.txt

cd /server
## [First Try]
# django-admin startproject tutorial
# cd tutorial 
# python manage.py startapp snippets

python manage.py makemigrations
python manage.py migrate
python manage.py runserver 0.0.0.0:8300