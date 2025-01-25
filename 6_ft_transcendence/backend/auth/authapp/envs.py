import os

from exceptions.CustomException import InternalException


def get_os_str(key: str) -> str:
    val: str | None = os.getenv(key)
    if val is None:
        raise InternalException()
    return val


def get_os_int(key: str) -> int:
    return int(get_os_str(key))


OAUTH_42_URL = get_os_str("OAUTH_42_URL")
OAUTH_TOKEN_URL = get_os_str("OAUTH_TOKEN_URL")
OAUTH_CLIENT_ID = get_os_str("OAUTH_CLIENT_ID")
OAUTH_CLIENT_SECRET = get_os_str("OAUTH_CLIENT_SECRET")

JWT_URL = get_os_str("JWT_URL")

OTP_SECRET = get_os_str("OTP_SECRET")
OTP_ISSUER = get_os_str("OTP_ISSUER")
