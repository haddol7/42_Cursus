#!/bin/bash

WP_PATH="/var/www/inception"
WP_CONFIG="$WP_PATH/wp-config.php"

if [ ! -f "$WP_CONFIG" ]; then
	echo -e "\033[31m<Inception Debug - WordPress> Init WordPress in $WP_PATH\033[0m"
	
    wget --no-check-certificate https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
    chmod +x wp-cli.phar
    mv wp-cli.phar /usr/local/bin/wp
    mv /tmp/wp-config.php "$WP_PATH"

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

echo -e "\033[31m <Inception Debug - WordPress> Setup Done\033[0m"

exec php-fpm7.4 --nodaemonize
