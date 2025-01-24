const rooms = {};

//아직 제대로 만들지 않음.
function initializeRoom(socket, roomCount) {
  const roomName = `room-${Math.floor(Object.keys(rooms).length / 2)}`;
  socket.join(roomName);

  if (!rooms[roomName]) {
    rooms[roomName] = {
      ball: { x: 0, y: 0, vx: 0.1, vy: 0.1 },
      paddles: { paddle1: 0, paddle2: 0 },
      scores: { paddle1: 0, paddle2: 0 },
      gameOver: false,
    };
  }

  const paddleId = roomCount % 2 === 0 ? "paddle1" : "paddle2";
  return { roomName, paddleId };
}

function handleDisconnect(roomName, socket, io) {
  socket.leave(roomName);
  io.to(roomName).emit("playerLeft");
}

function cleanupRooms(roomName, io) {
  if (!io.sockets.adapter.rooms.get(roomName)) {
    delete rooms[roomName];
  }
}

module.exports = { rooms, initializeRoom, handleDisconnect, cleanupRooms };
