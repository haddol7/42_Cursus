from http.client import (
    BAD_REQUEST,
    INTERNAL_SERVER_ERROR,
    NOT_FOUND,
    UNAUTHORIZED,
)


class CustomException(Exception):
    msg: str
    status_code: int

    def __init__(self, msg: str, status_code: int):
        self.msg = msg
        self.status_code = status_code

    def __str__(self) -> str:
        return self.msg

    def get_status_code(self) -> int:
        return self.status_code


class InternalException(CustomException):
    def __init__(self):
        super().__init__("internal_error", INTERNAL_SERVER_ERROR)


class UnauthenticatedException(CustomException):
    def __init__(self, msg="unauthenticated"):
        super().__init__(msg, UNAUTHORIZED)


class JwtInvalidException(UnauthenticatedException):
    def __init__(self):
        super().__init__("jwt.invalid")


class JwtExpiredException(UnauthenticatedException):
    def __init__(self):
        super().__init__("jwt.expired")


class TwoFARequiredException(UnauthenticatedException):
    def __init__(self):
        super().__init__("2fa.required")


class TwoFARegisterException(UnauthenticatedException):
    def __init__(self):
        super().__init__("2fa.register")


class BadRequestException(CustomException):
    def __init__(self):
        super().__init__("bad_request", BAD_REQUEST)


class BadRequestFieldException(BadRequestException):
    field: str

    def __init__(self, field: str):
        super().__init__()
        self.field = field

    def __str__(self) -> str:
        return super().__str__() + ":" + self.field


class BadRequestFoundException(BadRequestException):
    target: str

    def __init__(self, target: str):
        super().__init__()
        self.target = target

    def __str__(self) -> str:
        return f"{self.target}.{super().__str__()}"


class NotFoundException(CustomException):
    def __init__(self):
        super().__init__("not_found", NOT_FOUND)


class NotFoundSthException(NotFoundException):
    field: str

    def __init__(self, field: str):
        super().__init__()
        self.field = field

    def __str__(self) -> str:
        return super().__str__() + f":{self.field}"
