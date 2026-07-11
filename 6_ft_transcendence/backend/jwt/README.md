# JWT

내부 서버가 사용하는 엔드포인트입니다. 외부/프론트엔드에 노출되지 않습니다.

## Endpoint

사용할 엔드포인트들만 나열하였습니다. 나머지는 사용하지 않길 바랍니다.

엔드포인트 경로가 수시로 바뀔 수 있습니다. 변수화하여 변경에 잘 대응되도록 하기 바랍니다.

### POST /jwt/check

- Request

```json
{
    "jwt": "string",
    "skip_2fa": "boolean"
}
```

- Response

```json
{
    "user_id": "int"
}
```

jwt가 유효한지를 체크합니다. 이는 access token을 의미합니다.

jwt가 유효한 경우 200대 응답 코드와 `user_id`를 반환합니다.

- `{field}`가 올바르지 않은 경우, `bad_request:{field}`(400)
- `jwt`가 유효하지 않은 경우, `jwt.invalid` (401)
- `jwt`가 유효기간이 지난 경우, `jwt.expired` (401)
- `skip_2fa`가 False인데, `jwt`가 2FA 등록이 필요한 경우, `jwt.register` (401)
- `skip_2fa`가 False인데, `jwt`가 2FA 인증이 필요한 경우, `jwt.required` (401)
- 이외 내부 서버 에러인 경우, `internal_error` (500)

### POST /jwt/refresh

- Request

```json
{
    "refresh_token": "string"
}
```

- Response

```json
{
    "access_token": "string",
    "refresh_token": "string"
}
```

주어진 refresh token으로 새로운 access token과 refresh token을 만들어냅니다. 그렇게 만들어진 새로운 토큰을 반환합니다.

2FA가 이루어지지 않은 경우에도 새로운 JWT를 반환합니다.

- `{field}`가 올바르지 않은 경우, `bad_request:{field}` (400)
- `refresh_token`이 유효하지 않은 경우, `jwt.invalid` (401)
- `refresh_token`이 유효기간이 지난 경우, `jwt.expired` (401)
- 기타 내부 서버 에러, `internal_error` (500)


### POST /jwt/token

- Request

```json
{
    "user_id": "int",
    "twofa_delete": "boolean"
}
```

- Response

```json
{
    "access_token": "string",
    "refresh_token": "string",
    "isnew": "boolean"
}
```

!!! 올바른 사용자가 요청하는지 체크하지 않습니다 !!!

아예 새로운 JWT를 생성해 반환합니다.

- `twofa_delete`가 True이면 twofa 정보를 지우고 새로운 토큰을 반환합니다. 사용자는 twofa 인증을 통과해야 토큰을 사용할 수 있습니다.
- `twofa_delete`가 False 이면 twofa 정보를 지우지 않고 새로운 토큰을 반환합니다. 사용자는 새로운 토큰을 그대로 사용할 수 있습니다.

에러 목록은 다음과 같습니다.

- `{field}`가 올바르지 않은 경우, `bad_request:{field}` (400)
- 기타 내부 서버 에러, `internal_error` (500)

### DELETE /jwt/token (JWT)

- Query param
    - `user_id`: `int`


!!! 올바른 사용자가 요청하는지 체크하지 않습니다 !!! JWT로 인증된 사용자로 가정합니다.


`user_id` 사용자의 로그인을 지웁니다. 사용자가 이미 발급받은 JWT로는 더이상 인증할 수 없습니다.

만약 인증을 시도한다면, `jwt.invalid`가 반환됩니다.

- `{field}`가 올바르지 않은 경우, `bad_request:{field}` (400)
- 기타 내부 서버 에러, `internal_error` (500)

### GET /jwt/online

- Query param
    - `user_id`: `int`

- Response

```json
{
    "isonline": "boolean"
}
```

`user_id`를 가진 사용자가 현재 온라인인지를 반환합니다.

내부적으로, JWT 만료시간을 가지고 있어 그 만료시간이 지났는지를 체크하는 것으로 합니다.

사용자가 존재하지 않더라도 offline인 것으로 하고 에러를 반환하지 않습니다.

- `{field}`가 올바르지 않은 경우, `bad_request:{field}` (400)
- 기타 내부 서버 에러, `internal_error` (500)

### POST /jwt/token/ai

- Request

```json
{
    "match_id": "int",
}
```

- Response

```json
{
    "access_token": "string"
}
```

!!! 올바른 사용자가 요청하는지 체크하지 않습니다 !!!

아예 새로운 JWT를 생성해 반환합니다. 단, 이 JWT는 AI임을 인증합니다.

- `{field}`가 올바르지 않은 경우, `bad_request:{field}` (400)
- 기타 내부 서버 에러, `internal_error` (500)

### POST /jwt/check/ai

- Request

```json
{
    "jwt": "string"
}
```

- Response

```json
{
    "match_id": "int"
}
```

jwt가 유효한지를 체크합니다. 이는 access token을 의미합니다.

jwt가 유효한 경우 200대 응답 코드와 `match_id`를 반환합니다.

단, AI를 위한 JWT여야 합니다.

- `{field}`가 올바르지 않은 경우, `bad_request:{field}`(400)
- `jwt`가 유효하지 않은 경우, `jwt.invalid` (401)
- 이외 내부 서버 에러인 경우, `internal_error` (500)