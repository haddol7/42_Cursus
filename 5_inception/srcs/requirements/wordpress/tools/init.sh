#!/bin/bash

PHP_INI="/etc/php/7.4/fpm/php.ini"
WWW_CONF="/etc/php/7.4/fpm/pool.d/www.conf"

if grep -q ";cgi.fix_pathinfo=1" "$PHP_INI"; then
    sed -i 's/;cgi.fix_pathinfo=1/cgi.fix_pathinfo=0/g' "$PHP_INI"
fi

if grep -q "listen = /run/php/php7.4-fpm.sock" "$WWW_CONF"; then
    sed -i "s|listen = /run/php/php7.4-fpm.sock|listen = 9000|g" "$WWW_CONF"
    sed -i 's/;listen.mode = 0660/listen.mode = 0660/g' "$WWW_CONF"
    sed -i 's/;daemonize = yes/daemonize = no/g' "$WWW_CONF"
fi

WP_PATH="/var/www/inception"
WP_CONFIG="$WP_PATH/wp-config.php"

if [ ! -f "$WP_CONFIG" ]; then
    echo "Moving wp-config.php to $WP_PATH..."
	wget --no-check-certificate https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
	chmod +x wp-cli.phar
	mv wp-cli.phar /usr/local/bin/wp
	mkdir -p /run/php/
	mkdir -p /var/run/php/
	mkdir -p /var/www/inception/
    mv /tmp/wp-config.php "$WP_PATH"
    chown www-data:www-data "$WP_CONFIG"
fi

if [ ! -f "$WP_PATH/wp-load.php" ]; then
    echo "Downloading WordPress..."
    wp --allow-root --path="$WP_PATH" core download
fi

if ! wp --allow-root --path="$WP_PATH" core is-installed; then
    echo "Installing WordPress..."
    wp --allow-root --path="$WP_PATH" core install \
        --url="$WP_URL" \
        --title="$WP_TITLE" \
        --admin_user="$WP_ADMIN_USER" \
        --admin_password="$WP_ADMIN_PASSWORD" \
        --admin_email="$WP_ADMIN_EMAIL"

    echo "Creating additional WordPress user..."
    wp --allow-root --path="$WP_PATH" user create \
        "$WP_USER" \
        "$WP_EMAIL" \
        --user_pass="$WP_PASSWORD" \
        --role="$WP_ROLE"
else
    echo "WordPress is already installed. Skipping installation."
fi

exec php-fpm7.4 --nodaemonize
