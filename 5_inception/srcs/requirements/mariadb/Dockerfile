FROM	debian:bullseye

EXPOSE	3306

RUN		apt-get update -y && \
		apt-get install -y --no-install-recommends --no-install-suggests \
		mariadb-server \
		tini && \
		rm -rf /var/lib/apt/lists/* && \
		chmod +x tools/setup.sh

COPY	tools/setup.sh /bin/
COPY	conf/50-server.cnf /etc/mysql/mariadb.conf.d/

ENTRYPOINT ["/usr/bin/tini", "--"]
CMD ["/bin/setup.sh"]
