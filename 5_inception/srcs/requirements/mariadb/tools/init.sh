#!/bin/bash

echo -e "\033[31m<Inception Debug - mariadb> Init Database\033[0m"

service mariadb start

mariadb -u root <<EOF
CREATE DATABASE IF NOT EXISTS $DB_NAME;
CREATE USER IF NOT EXISTS '$DB_USER'@'%' IDENTIFIED BY '$DB_PASSWORD';
GRANT ALL PRIVILEGES ON $DB_NAME.* TO '$DB_USER'@'%';
SET PASSWORD FOR 'root'@'localhost' = PASSWORD('$DB_PASS_ROOT');
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY '$DB_PASS_ROOT' WITH GRANT OPTION;
FLUSH PRIVILEGES;
EOF

sleep 3

service mariadb stop

echo -e "\033[31m<Inception Debug - mariadb> Setup Done\033[0m"

exec mysqld_safe
