from typing import TYPE_CHECKING


if TYPE_CHECKING:
    from .match import Match


class MatchDict:
    match_dict_2: dict[int, "Match"]

    def __init__(self) -> None:
        self.match_dict_2 = {}

    def delete_match_id(self, match_id: int):
        del self.match_dict_2[match_id]

    def get_dict(self) -> dict[int, "Match"]:
        return self.match_dict_2

    def clear(self):
        self.match_dict_2 = {}

    def get(self, match_id: int) -> "Match | None":
        if match_id in self.match_dict_2:
            return self.match_dict_2[match_id]
        return None

    def get_room_by_userid(self, user_id: int) -> "Match | None":
        for match in self.match_dict_2.values():
            if match.is_user_connected(user_id):
                return match
        return None

    def __getitem__(self, match_id: int) -> "Match":
        ret = self.get(match_id)
        if ret is None:
            raise KeyError()
        return ret

    def __setitem__(self, key, value):
        self.match_dict_2[key] = value


match_dict = MatchDict()
