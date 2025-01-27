#!/bin/bash

curl -X POST -H "Content-Type:application/json" -d '{"user_id":"1"}' http://127.0.0.1:8100/jwt/user -v
sleep 3

curl -X POST -H "Content-Type:application/json" -d '{"user_id":"1"}' http://127.0.0.1:8100/jwt/new -v

#curl -X POST -H "Content-Type:application/json" -d '{"jwt":"1", "skip_2fa":"True"}' http://127.0.0.1:8100/jwt/check
