FROM	debian:bullseye

EXPOSE	3306

RUN		apt-get update -y && \
		apt-get install -y --no-install-recommends --no-install-suggests \
		mariadb-server \
		tini && \
		rm -rf /var/lib/apt/lists/* && \
		chmod +x /bin/setup.sh

COPY	conf/50-server.cnf /etc/mysql/mariadb.conf.d/
COPY	tools/setup.sh /bin/

ENTRYPOINT ["/usr/bin/tini", "--"]
CMD ["setup.sh"]
