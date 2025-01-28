#!/bin/bash

## 임시로 토큰 발행해서 db에 유저 생성
curl -X POST -H "Content-Type:application/json" -d '{"user_id":"1"}' http://127.0.0.1:8100/jwt/user -v
sleep 2

curl -X POST -H "Content-Type:application/json" -d '{"user_id":"1"}' http://127.0.0.1:8100/jwt/new -v

#curl -X POST -H "Content-Type:application/json" -d '{"jwt":"1", "skip_2fa":"True"}' http://127.0.0.1:8100/jwt/check

## GET request
# curl -X GET "http://127.0.0.1:8300/user/?user_name=asdf" \
# -H "Authorization: Bearer YOUR_JWT_TOKEN"

## PUT request
# curl -X PUT "http://127.0.0.1:8300/user/" \
# -H "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VyX2lkIjoxLCJ1c2VyX3NlY3JldCI6IkN0dE4zZGlxUUMiLCJleHAiOjE3MzgwNzg5Nzd9.Ny5kxzKLTWfwbH4EYTeFkz6Fea0FX1-ga00Td7icBbI" \
# -H "Content-Type: application/json" -d '{"memo":"hello asdf!"}' -v