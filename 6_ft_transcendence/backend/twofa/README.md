# twofa

2FA에 관련된 처리를 합니다.

## Endpoints

### GET /twofa/info

- QueryParam:
    - user_id: int
- Response:

```json
{
    "twofa_name": "string"
}
```

!!! 올바른 사용자가 요청하는지 체크하지 않습니다 !!!

`user_id`를 받아 그 사용자가 갖고 있는 이름을 반환합니다.

- `{field}`가 올바르지 않을 경우, `bad_request:{field}` (400)
- `user_id`로 저장된 UserInfo가 없는 경우, `2fa.register` (401)
- 기타 내부 서버 에러, `internal_error` (500)


### POST /twofa/info

- Request Body:

```json
{
    "user_id": "int",
    "name": "string"
}
```

- Response body:

```json
{
    "url": "string"
}
```

!!! 올바른 사용자가 요청하는지 체크하지 않습니다 !!!

`user_id`와 `name`을 받아 `url`을 생성해 반환합니다.

이미 `url`이 있었더라도 에러를 반환하지 않고 새로운 `url`을 생성해 반환합니다. 이 요청 전에 있었던 `url`은 무효화됩니다.

- `{field}`가 올바르지 않은 경우: `bad_request:{field}` (400)
- `user_id`를 가진 `User`가 존재하지 않는 경우: `not_found:user` (404)
- 기타 내부 서버 에러: `internal_error` (500)


### POST /twofa/code

- Request

```json
{
    "user_id": "int",
    "code": "str",
    "skip": "optional, bool"
}
```

!!! 올바른 사용자가 요청하는지 체크하지 않습니다 !!!

주어진 code가 맞는지 체크합니다. 맞다면 내부 정보를 업데이트합니다.

- `{field}`가 올바르지 않은 경우: `bad_request:{field}` (400)
- `user_id`로 된 `UserInfo`가 없는 경우: `2fa.register` (401)
- `code`가 틀린 경우: `bad_request:code` (400)
- 기타 내부 서버 에러: `interanl_error` (500)

### GET /twofa/check

- Query param
    - `user_id`: `int`

!!! 올바른 사용자가 요청하는지 체크하지 않습니다 !!!

이미 전에 2FA를 통과했는지를 반환합니다.

- `{field}`가 올바르지 않은 경우: `bad_request:{field}` (400)
- `user_id`로 된 UserInfo가 존재하지 않는 경우: `2fa.register` (401)
- `user_id` 사용자가 2FA를 통과하지 못한 경우: `2fa.required` (401)
- 기타 내부 서버 에러: `internal_error` (500)

### DELETE /twofa/check

- Quer param
    - `user_id`: `int`

!!! 올바른 사용자가 요청하는지 체크하지 않습니다 !!!

2FA를 통과하지 않은 것으로 필드를 업데이트합니다. 전에 통과를 안 했어도 에러를 내지 않습니다.

- `{field}`가 올바르지 않은 경우: `bad_request:{field}` (400)
- `user_id`로 된 UserInfo가 존재하지 않는 경우: `2fa.register` (401)
- 기타 내부 서버 에러: `internal_error` (500)