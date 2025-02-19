import logging
from gameapp.models import TempMatch, TempMatchRoom, TempMatchRoomUser, TempMatchUser


logger = logging.getLogger(__name__)


def clear_room(room_name: str):
    logger.info(f"clear_room room_name={room_name}")

    temp_room = TempMatchRoom.objects.get(room_name=room_name)
    room_user = TempMatchRoomUser.objects.filter(temp_match_room_id=temp_room.id)
    room_user.delete()

    temp_match = TempMatch.objects.filter(match_room_id=temp_room.id)
    temp_match_user = TempMatchUser.objects.filter(temp_match__in=temp_match)

    temp_match_user.delete()
    temp_match.delete()

    temp_room.delete()


def get_room_user_or_none(user_id: int):
    try:
        temp_match_room_user = TempMatchRoomUser.objects.get(user_id=user_id)
    except:
        temp_match_room_user = None
    return temp_match_room_user
