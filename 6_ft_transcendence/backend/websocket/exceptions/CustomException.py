from http.client import (
    BAD_REQUEST,
    FORBIDDEN,
    INTERNAL_SERVER_ERROR,
    NOT_FOUND,
    OK,
    UNAUTHORIZED,
)


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


class UnauthenticatedException(CustomException):
    def __init__(self, msg="unauthenticated"):
        super().__init__(msg)

    def get_status_code(self) -> int:
        return UNAUTHORIZED


class JwtInvalidException(UnauthenticatedException):
    def __init__(self):
        super().__init__("jwt.invalid")


class JwtExpiredException(UnauthenticatedException):
    def __init__(self):
        super().__init__("jwt.expired")


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


class TwoFaNotRegisterException(UnauthenticatedException):
    def __init__(self):
        super().__init__("2fa.register")


class TwoFaRequiredException(UnauthenticatedException):
    def __init__(self):
        super().__init__("2fa.required")


class ForbiddenException(CustomException):
    def __init__(self, msg: str = "forbidden"):
        super().__init__(msg)

    def get_status_code(self) -> int:
        return FORBIDDEN


class WebSocketRoomException(CustomException):
    def __init__(self, msg: str):
        super().__init__("room." + msg)


class WebSocketAlreadyRoomJoinedException(WebSocketRoomException):
    def __init__(self):
        super().__init__("joined")

    def get_status_code(self) -> int:
        return FORBIDDEN


class WebSocketRoomNotJoinedException(WebSocketRoomException):
    def __init__(self):
        super().__init__("not_joined")

    def get_status_code(self) -> int:
        return FORBIDDEN


class WebSocketRoomNotFoundException(WebSocketRoomException):
    def __init__(self):
        super().__init__("not_found")

    def get_status_code(self) -> int:
        return NOT_FOUND


class WebSocketRoomFullException(WebSocketRoomException):
    def __init__(self):
        super().__init__("full")

    def get_status_code(self) -> int:
        return FORBIDDEN


class WebSocketRoomNotFullException(WebSocketRoomException):
    def __init__(self):
        super().__init__("not_full")

    def get_status_code(self) -> int:
        return FORBIDDEN


class WebSocketUserAlreadyExists(CustomException):
    def __init__(self):
        super().__init__("user.found")

    def get_status_code(self) -> int:
        return FORBIDDEN


class WebSocketRoomNotAdminException(WebSocketRoomException):
    def __init__(self):
        super().__init__("not_admin")

    def get_status_code(self) -> int:
        return FORBIDDEN
