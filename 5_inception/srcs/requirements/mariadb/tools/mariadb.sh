#!/bin/bash

mysql_install_db --user=mysql --datadir=/var/lib/mysql

mysqld --datadir=/var/lib/mysql --bind-address=0.0.0.0 &

sleep 5

cat <<EOF | mysql
CREATE DATABASE IF NOT EXISTS ${DB_NAME};
CREATE USER IF NOT EXISTS '${DB_USER}'@'%' IDENTIFIED BY '${DB_PASSWORD}';
GRANT ALL PRIVILEGES ON ${DB_NAME}.* TO '${DB_USER}'@'%';
FLUSH PRIVILEGES;
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_DB_PASSWORD}';
EOF
