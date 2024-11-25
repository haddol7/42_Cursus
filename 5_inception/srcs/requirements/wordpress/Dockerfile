FROM	debian:bullseye

EXPOSE	9000

RUN		apt-get update && apt-get install -y \
		tini \
		ca-certificates \
		php7.4-fpm \
		php7.4-mysql \
		wget && \
		rm -rf /var/lib/apt/lists/*

COPY	conf/wp-config.php /tmp/
COPY	conf/www.conf /etc/php/7.4/fpm/pool.d/
COPY	tools/setup.sh /bin/

RUN		sed -i 's/;cgi.fix_pathinfo=1/cgi.fix_pathinfo=0/g' /etc/php/7.4/fpm/php.ini && \
		sed -i "s/listen = \/run\/php\/php7.4-fpm.sock/listen = 9000/g" /etc/php/7.4/fpm/pool.d/www.conf && \
		sed -i 's/;listen.mode = 0660/listen.mode = 0660/g' /etc/php/7.4/fpm/pool.d/www.conf && \
		wget --no-check-certificate https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
		chmod +x wp-cli.phar && \
		mv wp-cli.phar /usr/local/bin/wp && \
		mkdir -p /var/www/inception/ && \
		chown -R www-data:www-data /var/www/inception/ && \
		chmod +x /bin/setup.sh

ENTRYPOINT ["tini", "--"]
CMD		["setup.sh"]
