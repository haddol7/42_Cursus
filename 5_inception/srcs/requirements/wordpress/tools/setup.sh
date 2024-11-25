#!/bin/bash

[ ! -f "/var/www/inception/wp-config.php" ] && mv /tmp/wp-config.php /var/www/inception/

sleep 10

wp --allow-root --path="/var/www/inception/" core download || true

if ! wp --allow-root --path="/var/www/inception/" core is-installed; then
    wp --allow-root --path="/var/www/inception/" core install \
        --url="$WP_URL" \
        --title="$WP_TITLE" \
        --admin_user="$WP_ADMIN_USER" \
        --admin_password="$WP_ADMIN_PASSWORD" \
        --admin_email="$WP_ADMIN_EMAIL"
fi

wp --allow-root --path="/var/www/inception/" user get "$WP_USER" || \
    wp --allow-root --path="/var/www/inception/" user create \
        "$WP_USER" "$WP_EMAIL" \
        --user_pass="$WP_PASSWORD" \
        --role="$WP_ROLE"

exec php-fpm7.4 --nodaemonize
