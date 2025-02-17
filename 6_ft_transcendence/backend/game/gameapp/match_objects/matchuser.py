from typing import TypedDict

AI_ID = -1


class MatchUser(TypedDict):
    is_ai: bool
    sid: str
    id: int


class RealUser(MatchUser):
    name: str


class AiUser(MatchUser):
    pass
