import logging
from typing import TypedDict

from exceptions.CustomException import InternalException

AI_ID = -1

logger = logging.getLogger(__name__)


class MatchUser(TypedDict):
    is_ai: bool
    sid: str
    id: int


class RealUser(MatchUser):
    name: str


class AiUser(MatchUser):
    pass


def get_dto(is_ai: bool, sid: str, user_id: int, user_name: str | None):
    if is_ai:
        return AiUser(is_ai=is_ai, sid=sid, id=user_id)
    else:
        if user_name is None:
            logger.error(
                "When `is_ai` is False, expected `user_name` to be not None, but got None!"
            )
            raise InternalException()
        return RealUser(is_ai=is_ai, sid=sid, id=user_id, name=user_name)
