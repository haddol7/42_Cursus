const { WINNING_SCORE } = require("./constants");
const rooms = {};

// 클라이언트로부터 roomId 요청
function requestRoomIdfromClient(socket) {
  return new Promise((resolve) => {
    socket.emit("requestRoomId");
    socket.once("roomId", ({ roomId, isAI }) => {
      resolve({ roomId, isAI });
    });
  });
}

// 방 초기화 : 방 생성 및 paddleId 할당
function initializeRoom(roomId, socket) {
  // 방이 이미 존재하고, 게임이 이미 끝났다면 연결을 끊습니다.
  // 예) 새로고침을 했을 때
  if (rooms[roomId] && rooms[roomId].gameOver) {
    socket.disconnect(true);
    return { paddleId: null, roomCounter: rooms[roomId].count };
  }
  if (!rooms[roomId]) {
    rooms[roomId] = {
      ball: { x: 0, y: 0, vx: 0.1, vy: 0.1 },
      paddles: { paddle1: 0, paddle2: 0 },
      scores: { paddle1: 0, paddle2: 0 },
      gameOver: false,
      count: 1,
    };
  }

  if (roomId === "spectator") {
    // 디버그 : 관전자 모드
    console.log("spectator joined");
    socket.join("4242");
    return { paddleId: "spectator", roomCounter: rooms[roomId].count };
  }
  if (roomId === "4242") {
    rooms[roomId].scores.paddle1 = 0;
    rooms[roomId].scores.paddle2 = 0;
    rooms[roomId].gameOver = false;
    rooms[roomId].count++;
  }
  socket.join(roomId);
  const paddleId = rooms[roomId].count % 2 === 0 ? "paddle2" : "paddle1";
  return { paddleId, roomCounter: rooms[roomId].count };
}

function handleDisconnect(roomId, paddleId, socket, io) {
  console.log(`${roomId} - ${paddleId} disconnected`);
  if (!rooms[roomId] || paddleId === "spectator") return;
  io.to(roomId).emit("updateScore", { paddle1: 0, paddle2: 0 });
  io.to(roomId).emit("resetPositions", {});
  rooms[roomId].gameOver = false;
  rooms[roomId].count = 1;
}

module.exports = {
  rooms,
  requestRoomIdfromClient,
  initializeRoom,
  handleDisconnect,
};
