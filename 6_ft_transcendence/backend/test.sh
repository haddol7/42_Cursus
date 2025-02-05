#!/bin/bash

## 임시로 토큰 발행해서 db에 유저 생성
ACCESS_TOKENS=()

NAMES=('Smith' 'Johnson' 'Williams' 'Brown' 'Jones' 'Miller' 'Davis' 'Garcia' 'Taylor' 'Anderson')

for i in {1..10}
do
    curl -X POST -H "Content-Type:application/json" -d "{\"user_id\":\"$i\"}" http://127.0.0.1:8100/jwt/user #-v
    echo ''
    sleep 1
    token=$(curl -X POST -H "Content-Type:application/json" -d "{\"user_id\":\"$i\"}" http://127.0.0.1:8100/jwt/new | jq -r '.access_token')
    echo "ACCESS_TOKEN: $token" >> 'token.txt'

    ACCESS_TOKENS+=("$token")

    echo "/user GET request ->"
    curl -X GET "http://127.0.0.1:8300/user/?user_name=${NAMES[$((i - 1))]}" \
         -H "Authorization: Bearer ${ACCESS_TOKENS[$((i - 1))]}"
    echo ''
done

echo "/user PUT request ->"
curl -X PUT "http://127.0.0.1:8300/user/" \
        -H "Authorization: Bearer ${ACCESS_TOKENS[0]}" \
        -H "Content-Type: application/json" -d '{"memo":"hello django~~~!"}'
echo ''

for ((i = 0; i < 10; i++))
do
    echo "/user/friend POST request ->"
    curl -X POST "http://127.0.0.1:8300/user/friend" \
         -H "Authorization: Bearer ${ACCESS_TOKENS[0]}" \
         -H "Content-Type: application/json" -d "{\"user_name\":\"${NAMES[$i]}\"}"
    echo ''
done

echo "/user/friend GET request ->"
curl -X GET "http://127.0.0.1:8300/user/friend" \
        -H "Authorization: Bearer ${ACCESS_TOKENS[0]}"
echo ''

#curl -X POST -H "Content-Type:application/json" -d '{"jwt":"1", "skip_2fa":"True"}' http://127.0.0.1:8100/jwt/check

#curl -X POST -H "Content-Type:application/json" -d '{"user_id":"8", "result":"win"}' http://127.0.0.1:8300/_internal/dashboard -

#curl -X PUT -F "image_url=@/home/kapustin/tsen/backend/backend/mice.png" -F "user_name=chansjeo" -H "Authorization: Bearer <token>" http://127.0.0.1:8300/user/
