# JWT

## Endpoint

사용할 엔드포인트들만 나열하였습니다. 나머지는 사용하지 않길 바랍니다.

엔드포인트 경로가 수시로 바뀔 수 있습니다. 변수화하여 변경에 잘 대응되도록 하기 바랍니다.

### POST /jwt/check

```json
Request:
{
    "jwt": "string",
    "skip_2fa": "boolean, default=False"
}

Response:
{
    "user_id": "int"
}
```

jwt가 유효한지를 체크합니다. 이는 access token을 의미합니다.

jwt가 유효한 경우 200대 응답 코드와 `user_id`를 반환합니다.

에러가 나는 경우, 다음 중 하나를 반환합니다.

- `jwt`가 없는 경우, `BadRequestFieldException`(400, Bad Request)
- `jwt`가 유효하지 않은 경우, `JwtInvalidException` (401, Unauthorized)
- `jwt`가 유효기간이 지난 경우, `JwtExpiredException` (401, Unauthorized)
- `skip_2fa`가 False인데, `jwt`가 2FA 등록이 필요한 경우, `JwtNotRegisterException` (401, Unauthorized)
- `skip_2fa`가 False인데, `jwt`가 2FA 인증이 필요한 경우, `JwtRequiredException` (401, Unauthorized)
- 이외 내부 서버 에러인 경우, `InternalException` (500, Internal Error)

### POST /jwt/refresh

```json
Request:
{
    "refresh_token": "string"
}

Response:
{
    "access_token": "string",
    "refresh_token": "string"
}
```

refresh_token으로 access token을 반환합니다. 새로운 access token과 refresh token을 발급합니다.

에러가 나는 경우, 다음을 반환합니다.

- `refresh_token`이 주어지지 않은 경우, `BadRequestFieldException("refresh_token")` (400)
- `refresh_token`이 유효하지 않은 경우, `JwtInvalidException()` (401)
- `refresh_token`이 유효기간이 지난 경우, `JwtExpiredException()` (401)
- 이외 내부 서버 에러인 경우, `InternalException()`


### POST /jwt/new

```json
Request:
{
    "user_id": "int"
}

Response:
{
    "access_token": "string",
    "refresh_token": "string"
}
```

아예 새로운 JWT를 생성해 반환합니다.

- `user_id`가 주어지지 않은 경우, `BadRequestFieldException("user_id")` (400)
- 이외 내부 서버 에러인 경우, `InternalException()`
