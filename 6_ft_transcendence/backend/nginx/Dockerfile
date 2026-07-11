FROM nginx:1.27.3-alpine

RUN apk add --no-cache openssl

COPY ./nginx.conf /etc/nginx/nginx.conf

COPY ./default.png /usr/share/nginx/html/media/default.png

COPY ./script.sh /script.sh
RUN chmod +x /script.sh

ENTRYPOINT [ "/script.sh" ]