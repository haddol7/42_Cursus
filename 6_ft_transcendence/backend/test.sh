#!/bin/bash

curl -X POST -H "Content-Type:application/json" -d '{"user_id":"1"}' http://127.0.0.1:8100/jwt/user
curl -X POST -H "Content-Type:application/json" -d '{"user_id":"1"}' http://127.0.0.1:8100/jwt/new