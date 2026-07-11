import os

from exceptions.CustomException import InternalException


def get_os_str(key: str) -> str:
    val: str | None = os.getenv(key)
    if val is None:
        raise InternalException()
    return val


def get_os_int(key: str) -> int:
    return int(get_os_str(key))


OTP_SECRET = get_os_str("OTP_SECRET")
OTP_ISSUER = get_os_str("OTP_ISSUER")

FRONTEND_URL = get_os_str("FRONTEND_URL")
