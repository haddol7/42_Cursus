FROM	debian:bullseye

EXPOSE	443

RUN		apt-get update && apt-get install -y nginx openssl tini

RUN mkdir -p /etc/nginx/certs/ && \
	openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
    -out /etc/nginx/certs/certificate.crt \
    -keyout /etc/nginx/certs/certificate.key \
    -subj "/C=KR/ST=Seoul/L=Seoul/O=42/OU=42seoul/CN=daeha.42.fr"

COPY	conf/nginx.conf	/etc/nginx/
COPY	conf/server.conf	/etc/nginx/conf.d/

RUN		mkdir -p /var/www/
RUN		chown -R www-data:www-data /var/www/

ENTRYPOINT ["tini", "--", "nginx", "-g", "daemon off;"]
