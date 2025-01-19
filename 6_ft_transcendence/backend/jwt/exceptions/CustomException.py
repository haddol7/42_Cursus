class CustomException(Exception):
    def __init__(self, msg: str):
        self.msg = msg

    def __str__(self) -> str:
        return self.msg


class InternalException(CustomException):
    def __init__(self):
        super().__init__("internal_error")


class JwtInvalidException(CustomException):
    def __init__(self):
        super().__init__("jwt.invalid")


class JwtExpiredException(CustomException):
    def __init__(self):
        super().__init__("jwt.expired")


class BadRequestFieldException(CustomException):
    field: str

    def __init__(self, field: str):
        super().__init__("bad_request")
        self.field = field

    def __str__(self) -> str:
        return super().__str__() + ":" + self.field
