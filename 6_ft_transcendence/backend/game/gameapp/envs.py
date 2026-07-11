import os

from exceptions.CustomException import InternalException


def get_os_str(key: str) -> str:
    val: str | None = os.getenv(key)
    if val is None:
        raise InternalException()
    return val


def get_os_int(key: str) -> int:
    return int(get_os_str(key))


USER_URL = get_os_str("USER_URL")
JWT_URL = get_os_str("JWT_URL")
GAME_URL = get_os_str("GAME_URL")
GAMEAI_URL = get_os_str("GAMEAI_URL")
FRONTEND_URL = get_os_str("FRONTEND_URL")
WINNING_SCORE = get_os_int("WINNING_SCORE")
