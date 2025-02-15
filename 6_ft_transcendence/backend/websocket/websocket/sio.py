import json
from logging import Logger
from typing import Any
import socketio
from websocket.envs import FRONTEND_URL

sio = socketio.Server(
    cors_allowed_origins=["https://localhost", f"https://{FRONTEND_URL}"]
)

logger = Logger(__name__)

ROOM_LISTENERS = "room_listeners"
ROOM_LIST_EVENT = "room_list"
ROOM_CHANGED_EVENT = "room_changed"
START_GAME_EVENT = "start_game"

ROOM_LIMIT_VALID_VALUES = [2, 4, 8, 16]


def sio_emit(event: str, data: dict[str, Any], to: str):
    logger.info(f"emit event={event}, data={json.dumps(data)}, to={to}")
    return sio.emit(event, data=data, to=to)
