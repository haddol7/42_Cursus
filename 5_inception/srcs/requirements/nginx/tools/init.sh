#!/bin/bash

CERT_DIR="/etc/nginx/certs"
CERT_FILE="$CERT_DIR/certificate.crt"
KEY_FILE="$CERT_DIR/certificate.key"

echo -e "\033[31m<Inception Debug - nginx> Creating SSL certificate\033[0m"

mkdir -p "$CERT_DIR"
openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
    -out "$CERT_FILE" \
    -keyout "$KEY_FILE" \
    -subj "/C=KR/ST=Seoul/L=Seoul/O=42/OU=42seoul/CN=daeha.42.fr"

echo -e "\033[31m<Inception Debug - nginx> Setup Done\033[0m"

exec nginx -g "daemon off;"
