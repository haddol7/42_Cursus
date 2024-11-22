FROM debian:bullseye

RUN apt-get update -y && \
	apt upgrade -y && \
	apt install -y \
	wget \
	curl \
    php8.1 \
	php8.1-cli \
	php8.1-fpm \
	php8.1-mysql \
    php8.1-gd \
	php8.1-mbstring \
	php8.1-xml

COPY ./conf/www.conf /etc/php/8.1/fpm/pool.d/

RUN mkdir -p /run/php /var/www/html

COPY ./tools/wordpress.sh /usr/local/bin/wordpress.sh

RUN chmod +x /usr/local/bin/wordpress.sh

WORKDIR /var/www/html/

EXPOSE 9000

ENTRYPOINT ["/usr/bin/tini"]

CMD ["/usr/local/bin/wordpress.sh /usr/sbin/php-fpm8.1 -F"]

