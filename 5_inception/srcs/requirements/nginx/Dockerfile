FROM debian:bullseye

RUN apt-get update && \
	apt-get upgrade && \
	apt-get install -y nginx openssl

RUN mkdir -p /etc/nginx/ssl /etc/nginx/conf.d /etc/nginx/sites-available /run/nginx

COPY ./conf/default /etc/nginx/sites-available/default
COPY ./conf/default /etc/nginx/default
COPY ./tools/nginx.sh /var/www/nginx.sh

RUN chmod +x /var/www/nginx.sh

EXPOSE 443

ENTRYPOINT ["/usr/bin/tini", "--", "/var/www/nginx.sh"]

CMD ["nginx", "-g", "daemon off;"]
