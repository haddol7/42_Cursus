FROM debian:bullseye

RUN apt-get update && \
	apt-get upgrade && \
	apt-get install -y tini && \
	apt-get install -y mariadb-server

COPY ./tools/mariadb.sh /var/www/mariadb.sh

RUN chmod +x /var/www/mariadb.sh

EXPOSE 3306

ENTRYPOINT ["/usr/bin/tini"]

CMD ["/var/www/mariadb.sh"]
