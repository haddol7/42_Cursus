FROM	debian:bullseye

EXPOSE	3306

RUN		apt-get update -y && \
		apt-get install -y --no-install-recommends --no-install-suggests \
		mariadb-server \
		tini

COPY	conf/50-server.cnf /etc/mysql/mariadb.conf.d/

COPY	tools/setup.sh /bin/
RUN		chmod +x /bin/setup.sh

ENTRYPOINT ["tini", "--", "setup.sh", "mysqld_safe"]
