FROM	debian:bullseye

EXPOSE	3306

RUN		apt-get update && \
		mariadb-server && \
		rm -rf /var/lib/apt-get/lists/*

COPY	conf/50-server.cnf /etc/mysql/mariadb.conf.d/

COPY	tools/setup.sh /bin/
RUN		chmod +x /bin/setup.sh

CMD		["setup.sh", "mysqld_safe"]
