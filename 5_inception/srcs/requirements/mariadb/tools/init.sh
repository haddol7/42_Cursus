#!/bin/bash

DB_INIT_FILE="/var/lib/mysql/.db_initialized"

if [ ! -f "$DB_INIT_FILE" ]; then
    echo "Initializing MariaDB database..."

    mysqld --initialize-insecure --user=mysql
    mysqld_safe --skip-networking &

    sleep 5

    mariadb -u root <<EOF
CREATE DATABASE IF NOT EXISTS ${DB_NAME};
CREATE USER IF NOT EXISTS '${DB_USER}'@'%' IDENTIFIED BY '${DB_PASSWORD}';
GRANT ALL PRIVILEGES ON ${DB_NAME}.* TO '${DB_USER}'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_PASS_ROOT}';
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY '${DB_PASS_ROOT}' WITH GRANT OPTION;
FLUSH PRIVILEGES;
EOF

    touch "$DB_INIT_FILE"

    echo "MariaDB database initialized."
    killall mysqld_safe
    sleep 5
else
    echo "Database already initialized. Skipping setup."
fi

exec mysqld
