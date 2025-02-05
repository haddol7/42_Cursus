const { WINNING_SCORE } = require("./constants");
const rooms = {};

// 클라이언트로부터 roomId 요청
function requestRoomIdfromClient(socket) {
  return new Promise((resolve) => {
    socket.emit("requestRoomId");
    socket.once("roomId", (roomId) => {
      resolve(roomId);
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
  } else if (rooms[roomId].count === 1) rooms[roomId].count = 2;
  else {
    // 3명 이상일 때 연결을 끊습니다.
    console.log("Room is full");
    socket.disconnect(true);
    return { paddleId: null, roomCounter: rooms[roomId].count };
  }
  socket.join(roomId);
  const paddleId = rooms[roomId].count % 2 === 0 ? "paddle1" : "paddle2";
  return { paddleId, roomCounter: rooms[roomId].count };
}

function handleDisconnect(roomId, paddleId, socket, io) {
  console.log(`${roomId} - ${paddleId} disconnected`);
  if (!rooms[roomId]) return;
  // 게임 종료 조건 처리 (한 명이 나갔을 때)
  if (rooms[roomId].count === 2) {
    if (paddleId === "paddle1") {
      rooms[roomId].scores.paddle2 = WINNING_SCORE; // paddle2가 승리
    } else if (paddleId === "paddle2") {
      rooms[roomId].scores.paddle1 = WINNING_SCORE; // paddle1이 승리
    }
    const scores = rooms[roomId].scores;
    io.to(roomId).emit("updateScore", scores);
    io.to(roomId).emit("gameOver", {
      winner: paddleId === "paddle1" ? "paddle2" : "paddle1",
      paddle1: scores.paddle1,
      paddle2: scores.paddle2,
    });
    rooms[roomId].gameOver = true;
  }

  // 방에 남은 사람이 없을 때 방 삭제
  rooms[roomId].count--;
  if (rooms[roomId].count === 0) {
    delete rooms[roomId];
    console.log(`${roomId} - deleted`);
  } else if (rooms[roomId].count === 1) {
    console.log(`${roomId} - ${paddleId} player left`);
  }
}

module.exports = {
  rooms,
  requestRoomIdfromClient,
  initializeRoom,
  handleDisconnect,
};
