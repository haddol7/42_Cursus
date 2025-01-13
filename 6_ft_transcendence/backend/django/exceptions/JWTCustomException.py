from exceptions.CustomException import CustomException


class JWTExpired(CustomException):
    def __init__(self):
        super().__init__("jwt.invalid")
