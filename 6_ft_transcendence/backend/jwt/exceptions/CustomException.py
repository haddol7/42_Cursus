from http.client import BAD_REQUEST, INTERNAL_SERVER_ERROR, OK, UNAUTHORIZED


class CustomException(Exception):
    def __init__(self, msg: str):
        self.msg = msg

    def __str__(self) -> str:
        return self.msg

    def get_status_code(self) -> int:
        return OK


class InternalException(CustomException):
    def __init__(self):
        super().__init__("internal_error")

    def get_status_code(self) -> int:
        return INTERNAL_SERVER_ERROR


class JwtInvalidException(CustomException):
    def __init__(self):
        super().__init__("jwt.invalid")

    def get_status_code(self) -> int:
        return UNAUTHORIZED


class JwtExpiredException(CustomException):
    def __init__(self):
        super().__init__("jwt.expired")

    def get_status_code(self) -> int:
        return UNAUTHORIZED


class BadRequestException(CustomException):
    def __init__(self):
        super().__init__("bad_request")

    def get_status_code(self) -> int:
        return BAD_REQUEST


class BadRequestFieldException(BadRequestException):
    field: str

    def __init__(self, field: str):
        super().__init__()
        self.field = field

    def __str__(self) -> str:
        return super().__str__() + ":" + self.field
