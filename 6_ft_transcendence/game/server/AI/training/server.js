const express = require("express");
const { createServer } = require("http");
const { Server } = require("socket.io");
const path = require("path");
const {
  requestRoomIdfromClient,
  initializeRoom,
  handleDisconnect,
} = require("./roomManager");
const { startBallMovement, handlePaddleMove } = require("./gameLogic");

const app = express();
const httpServer = createServer(app);
const io = new Server(httpServer);

app.use(express.static(path.join(__dirname, "../../client")));
app.get("/", (req, res) => {
  res.sendFile(path.join(__dirname, "../../client/index.html"));
});

io.on("connection", async (socket) => {
  // 클라이언트로부터 roomId 요청
  // 디버그 : roomId은 client.js에서 정의한 DEBUG_ROOMCODE를 받습니다.
  let roomId = await requestRoomIdfromClient(socket);

  //방 생성 및 paddleId 할당
  const { paddleId, roomCounter } = initializeRoom(roomId, socket);
  console.log(`room : ${roomId} - ${paddleId} connected`);

  if (roomId === "spectator") {
    roomId = "4242";
  }
  // 클라이언트에 paddleId 전달 및 초기화
  socket.emit("init", { paddleId });

  // 방에 2명이 들어왔다면, 게임 시작
  if (roomCounter === 2) {
    startBallMovement(roomId, io);
  }

  // 상대 패들 이동 시 상태 업데이트
  socket.on("paddleMove", (data) => {
    handlePaddleMove(roomId, data, io);
  });

  // 유저가 나갔을 때 (승리 처리 및 방 삭제)
  socket.on("disconnect", (socket) => {
    handleDisconnect(roomId, paddleId, socket, io);
  });
});

const PORT = 3000;
httpServer.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
