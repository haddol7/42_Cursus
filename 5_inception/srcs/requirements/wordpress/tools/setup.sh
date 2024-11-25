#!/bin/bash

mv /tmp/wp-config.php /var/www/inception/

wp --allow-root --path="/var/www/inception/" core download

wp --allow-root --path="/var/www/inception/" core install \
    --url=$WP_URL \
    --title=$WP_TITLE \
    --admin_user=$WP_ADMIN_USER \
    --admin_password=$WP_ADMIN_PASSWORD \
    --admin_email=$WP_ADMIN_EMAIL

wp --allow-root --path="/var/www/inception/" user create \
    $WP_USER \
    $WP_EMAIL \
    --user_pass=$WP_PASSWORD \
    --role=$WP_ROLE

exec php-fpm7.4 --nodaemonize

