# Auth

다음 엔드포인트가 공개되어 있습니다.

## GET /auth/42/code

- Query params
    - `code`: `str`
- Response

```json
{
    "accessToken": "string",
    "refreshToken": "string",
    "isnew": "boolean"
}
```

42 Auth로 code를 보내고 그것이 올바른 경우 새로운 유저를 만듭니다. 그리고 accessToken과 refreshToken을 발급하여 반환합니다.

`isnew` 필드는 해당 사용자가 새롭게 생성된 사용자인지 아닌지를 나타냅니다. 만약 새롭게 생성된 사용자라면, 2FA를 등록해야 함을 의미하고, 그렇지 않다면 2FA 인증을 해야 함을 의미합니다.

- `{field}`가 올바르지 않은 경우: `bad_request:{field}` (400)
- `code`로 42 oauth 인증을 실패할 경우: `unauthenticated` (401)
- 기타 내부 서버 에러: `internal_error` (500)

## POST /auth/refresh

- Request

```json
{
    "refreshToken": "string"
}
```

- Response

```json
{
    "accessToken": "string",
    "refreshToken": "string"
}
```

`refreshToken`을 받아 새로운 `accessToken`과 `refreshToken`을 발급해 반환합니다.

2FA를 통과했는지는 체크하지 않습니다.

- `{field}`가 올바르지 않은 경우, `bad_request:{field}` (400)
- `refresh_token`이 유효하지 않은 경우, `jwt.invalid` (401)
- `refresh_token`이 유효기간이 지난 경우, `jwt.expired` (401)
- 기타 내부 서버 에러, `internal_error` (500)



## GET /auth/2fa (JWT)

- Response

```json
{
    "name": "string"
}
```

2FA가 있다면, 등록된 2FA의 name을 반환합니다.

JWT 체크할 때 2FA를 통과했는지는 체크하지 않습니다.

- JWT 토큰이 올바르지 않은 경우, `jwt.invalid`, `jwt.expired` (401)
- `{field}`가 올바르지 않은 경우, `bad_request:{field}` (400)
- `user_id`로 저장된 UserInfo가 없는 경우, `2fa.register` (401)
- 기타 내부 서버 에러, `internal_error` (500)



## POST /auth/2fa/new (JWT)

- Request

```json
{
    "name": "string"
}
```

- Repsonse

```json
{
    "url": "string"
}
```

새롭게 2FA를 발급해줍니다.

JWT 체크할 때 2FA를 통과했는지는 체크하지 않습니다.

- JWT 토큰이 올바르지 않은 경우, `jwt.invalid`, `jwt.expired` (401)
- `{field}`가 올바르지 않은 경우, `bad_request:{field}` (400)
- 기타 내부 서버 에러, `internal_error` (500)


## POST /auth/2fa (JWT)

- Request

```json
{
    "code": "string"
}
```

`code`가 올바른지를 검증받습니다. 2FA를 이미 등록하였고, 인증이 필요한 사용자가 사용합니다.

- JWT 토큰이 올바르지 않은 경우, `jwt.invalid`, `jwt.expired` (401)
- `{field}`가 올바르지 않은 경우: `bad_request:{field}` (400)
- `user_id`로 된 `UserInfo`가 없는 경우: `2fa.register` (401)
- `code`가 틀린 경우: `bad_request:code` (400)
- 기타 내부 서버 에러, `internal_error` (500)


## DELETE /auth/logout (JWT)

사용자가 가진 JWT 토큰으로 인증 후, 그 JWT 토큰을 무효화합니다.

나중에 동일한 JWT 토큰으로 인증을 시도한다면 `jwt.invalid`를 반환받습니다.

- JWT 토큰이 올바르지 않은 경우, `jwt.invalid`, `2fa.register`, `2fa.required`, `jwt.expired` (401)
- 기타 내부 서버 에러, `internal_error` (500)

## GET /auth/42/code/mock

- Query Param
    - `code`: `str`, 무시합니다.
    - `user_name`: `str`

- Response

```json
{
    "accessToken": "string",
    "refreshToken": "string",
    "isnew": "boolean"
}
```

`user_name` 의 사용자를 생성합니다. intra에 요청날리는 과정이 생략됩니다.

`/auth/42/code`의 응답 형식을 그대로 따라합니다.

## POST /auth/2fa/mock (JWT)

코드로 인증했다 치고 내부 상태를 인증 된 것으로 바꿉니다. 코드를 보내든, 안 보내든 상관 없습니다. 그냥 인증을 시켜줍니다.

`/auth/2fa`의 동작을 따라합니다.

# To User Backend

## POST /_internal/user

- Request

```json
{
    "user_id": "int",
    "user_name": "string"
}
```

회원가입이 될 때마다 요청을 보냅니다. `user_name`은 인트라 아이디입니다.
