import os

from exceptions.CustomException import InternalException


def get_os_str(key: str) -> str:
    val: str | None = os.getenv(key)
    if val is None:
        raise InternalException()
    return val


def get_os_int(key: str) -> int:
    return int(get_os_str(key))


TWOFA_URL = get_os_str("TWOFA_URL")
AI_USERID = get_os_str("AI_USERID")

JWT_EXPIRE_SECONDS = get_os_int("JWT_EXPIRE_SECONDS")
JWT_AI_EXPIRE_SECONDS = get_os_int("JWT_AI_EXPIRE_SECONDS")
JWT_REFRESH_EXPIRE_SECONDS = get_os_int("JWT_REFRESH_EXPIRE_SECONDS")
JWT_SECRET = get_os_str("JWT_SECRET")
JWT_ALGORITHM = get_os_str("JWT_ALGORITHM")

FRONTEND_URL = get_os_str("FRONTEND_URL")
