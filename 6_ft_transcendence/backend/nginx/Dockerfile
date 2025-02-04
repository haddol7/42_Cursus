FROM nginx:1.27.3-alpine

RUN apk add --no-cache openssl

COPY ./nginx.conf /etc/nginx/nginx.conf

COPY ./script.sh /script.sh
RUN chmod +x /script.sh

ENTRYPOINT [ "/script.sh" ]