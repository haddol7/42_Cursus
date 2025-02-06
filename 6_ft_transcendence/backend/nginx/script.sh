#!/bin/ash

sed -i 's/${SERVER_NAME}/'$SERVER_NAME'/g' /etc/nginx/nginx.conf
sed -i 's/${CRT_FILEPATH}/'$(echo $CRT_FILEPATH | sed 's/\//\\\//g')'/g' /etc/nginx/nginx.conf
sed -i 's/${KEY_FILEPATH}/'$(echo $KEY_FILEPATH | sed 's/\//\\\//g')'/g' /etc/nginx/nginx.conf
sed -i 's/${AUTH_PORT}/'$AUTH_PORT'/g' /etc/nginx/nginx.conf
sed -i 's/${JWT_PORT}/'$JWT_PORT'/g' /etc/nginx/nginx.conf
sed -i 's/${TWOFA_PORT}/'$TWOFA_PORT'/g' /etc/nginx/nginx.conf
sed -i 's/${ROOM_PORT}/'$ROOM_PORT'/g' /etc/nginx/nginx.conf
sed -i 's/${GAME_PORT}/'$GAME_PORT'/g' /etc/nginx/nginx.conf
sed -i 's/${USER_PORT}/'$USER_PORT'/g' /etc/nginx/nginx.conf

if [ ! -f $KEY_FILEPATH ] || [ ! -f $CRT_FILEPATH ]; then
  mkdir -p $(dirname $KEY_FILEPATH)
  rm -f $KEY_FILEPATH $CRT_FILEPATH

  openssl req -new -x509 -days 365 -nodes \
    -keyout $KEY_FILEPATH \
    -out $CRT_FILEPATH \
    -subj "/C=KR/ST=Seoul/L=Gwangjin/O=$SERVER_NAME/CN=$SERVER_NAME/emailAddress=$ADMIN_EMAIL/OU=Organization"
fi

exec nginx -g "daemon off;"