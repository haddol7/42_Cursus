#!/bin/bash

WP_PATH="/var/www/inception"
WP_CONFIG="$WP_PATH/wp-config.php"

if [ ! -f "$WP_CONFIG" ]; then
    echo "<Inception Debug> Init config in $WP_PATH..."
	sed -i 's/;daemonize = yes/daemonize = no/g' /etc/php/7.4/fpm/php-fpm.conf
    wget --no-check-certificate https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
    chmod +x wp-cli.phar
	mkdir -p /run/php
	mkdir -p /var/run/php
    mv wp-cli.phar /usr/local/bin/wp
    mkdir -p /var/www/inception/
    mv /tmp/wp-config.php "$WP_PATH"
fi

chown www-data:www-data "$WP_CONFIG"

if [ ! -f "$WP_PATH/wp-load.php" ]; then
    echo "<Inception Debug> Downloading WordPress..."
    wp core download --allow-root --path="$WP_PATH"
	
    wp core install \
    	--url=$WP_URL \
        --title=$WP_TITLE \
        --admin_user=$WP_ADMIN_USER \
        --admin_password=$WP_ADMIN_PASSWORD \
        --admin_email=$WP_ADMIN_EMAIL \
		--allow-root --path="$WP_PATH"

    wp user create \
        $WP_USER \
        $WP_EMAIL \
        --user_pass=$WP_PASSWORD \
        --role=$WP_ROLE \
		--allow-root --path="$WP_PATH" 
fi

exec php-fpm7.4 --nodaemonize
