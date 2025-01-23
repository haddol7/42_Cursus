//TODO : 클라이언트 사이드 공 위치 계산 (공 벡터만 전송)
//클라이언트 재접속 시 게임 상태 유지
//패들 충돌 자연스럽게

const express = require("express");
const { createServer } = require("http");
const { Server } = require("socket.io");
const path = require("path");
const { initializeRoom } = require("./roomManager");
const { startBallMovement, handlePaddleMove } = require("./gameLogic");

const app = express();
const httpServer = createServer(app);
const io = new Server(httpServer);

const {
  GAME_BOUNDS,
  BALL_RADIUS,
  PADDLE_HEIGHT,
  PADDLE_WIDTH,
  WINNING_SCORE,
} = require("./constants");

let roomCounter = 0;
const rooms = {};

app.use(express.static(path.join(__dirname, "../client")));

app.get("/", (req, res) => {
  res.sendFile(path.join(__dirname, "../client/index.html"));
});

// 소켓 연결
io.on("connection", (socket) => {
  //TODO : Pair에 맞게 방에 접속할 수 있게 하도록 구현
  //2명씩 방 생성
  const { roomName, paddleId } = initializeRoom(socket, roomCounter);
  console.log(`${roomName} - ${paddleId} connected`);
  socket.emit("init", { roomName, paddleId });
  roomCounter++;

  // 상대 패들 이동 시 상태 업데이트
  socket.on("paddleMove", (data) => {
    handlePaddleMove(roomName, data, io);
  });

  // 방에 2명이 들어왔다면, 게임 시작
  if (roomCounter % 2 === 0) {
    startBallMovement(roomName, io);
  }

  // 유저가 나갔을 때
  // TODO : 모두 게임에서 나갔을 때 방을 삭제 해야 함
  socket.on("disconnect", () => {
    console.log("A user disconnected");
  });
});

const PORT = 3000;
httpServer.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
