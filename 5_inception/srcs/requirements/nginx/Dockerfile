FROM	debian:bullseye

EXPOSE	443

RUN		apt-get update && \
		apt-get install -y --no-install-recommends --no-install-suggests \
		nginx \
		openssl \
		tini && \
		rm -rf /var/lib/apt/lists/* && \
	 	mkdir -p /etc/nginx/certs/ && \
		openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes -out /etc/nginx/certs/certificate.crt -keyout /etc/nginx/certs/certificate.key -subj "/C=KR/ST=Seoul/L=Seoul/O=42/OU=42seoul/CN=daeha.42.fr" && \
		mkdir -p /var/www/ && \
		chown -R www-data:www-data /var/www/

COPY	conf/nginx.conf		/etc/nginx/
COPY	conf/server.conf	/etc/nginx/conf.d/

ENTRYPOINT ["/usr/bin/tini", "--"]
CMD ["nginx", "-g", "daemon off;"]
