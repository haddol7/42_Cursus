import socketio
from websocket.envs import FRONTEND_URL

sio = socketio.Server(cors_allowed_origins=["https://localhost", f"https://{FRONTEND_URL}"])
