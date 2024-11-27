FROM debian:bullseye

EXPOSE 443

RUN apt-get update && \
    apt-get install -y --no-install-recommends --no-install-suggests \
    nginx \
    openssl \
    tini && \
    rm -rf /var/lib/apt/lists/* && \
    mkdir -p /var/www/ && \
    chown -R www-data:www-data /var/www/

COPY conf/nginx.conf /etc/nginx/
COPY conf/server.conf /etc/nginx/conf.d/

COPY init.sh /bin/init.sh
RUN chmod +x /bin/init.sh

ENTRYPOINT ["/usr/bin/tini", "--"]
CMD ["/bin/init.sh"]
