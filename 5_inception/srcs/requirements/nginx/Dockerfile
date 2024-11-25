FROM	debian:bullseye

EXPOSE	443

RUN		apt-get update && apt-get install -y nginx openssl

RUN mkdir -p /etc/nginx/certs/ && \
	openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
    -out /etc/nginx/certs/certificate.crt \
    -keyout /etc/nginx/certs/certificate.key \
    -subj "/C=KR/ST=Seoul/L=Seoul/O=42/OU=42seoul/CN=daeha.42.fr"

COPY	conf/nginx.conf	/etc/nginx/
COPY	conf/server.conf	/etc/nginx/conf.d/

RUN		echo "\tserver name daeha.42.fr;\n\
			\tssl_certificate /etc/nginx/certs/certificate.crt;\n\
			\tssl_certificate_key /etc/nginx/certs/certificate.key;\n\
			}" >> /etc/nginx/conf.d/server.conf

RUN		mkdir -p /var/www/
RUN		chown -R www-data:www-data /var/www/

CMD		["nginx", "-g", "daemon off;"]
