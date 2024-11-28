FROM debian:bullseye

EXPOSE 9000

RUN apt-get update -y && \
    apt-get install -y --no-install-recommends --no-install-suggests \
    tini \
    ca-certificates \
    php7.4-fpm \
    php7.4-mysql \
    wget && \
    rm -rf /var/lib/apt/lists/* && \
	mkdir -p /run/php /var/run/php /var/www/inception/ && \
	chown www-data:www-data /var/www/inception/ && \
	sed -i 's/;daemonize = yes/daemonize = no/g' /etc/php/7.4/fpm/php-fpm.conf

COPY conf/wp-config.php /tmp/
COPY conf/www.conf /etc/php/7.4/fpm/pool.d/
COPY tools/init.sh /bin/

RUN chmod +x /bin/init.sh

ENTRYPOINT ["/usr/bin/tini", "--"]
CMD ["/bin/init.sh"]
