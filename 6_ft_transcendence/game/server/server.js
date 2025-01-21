const express = require("express");
const { createServer } = require("http");
const { Server } = require("socket.io");
const path = require("path");

const app = express();
const httpServer = createServer(app);
const io = new Server(httpServer);

let roomCounter = 0;
const rooms = {};

const GAME_BOUNDS = { x: 5, y: 5 }; // Game boundaries
const PADDLE_WIDTH = 1; // Paddle width
const PADDLE_HEIGHT = 0.2; // Paddle height
const BALL_RADIUS = 0.2; // Ball radius
const WINNING_SCORE = 10; // Score needed to win

// client 디렉토리를 정적 파일 루트로 설정
app.use(express.static(path.join(__dirname, "../client")));

// 루트 경로 처리
app.get("/", (req, res) => {
  res.sendFile(path.join(__dirname, "../client/index.html"));
});

io.on("connection", (socket) => {
  console.log("A user connected");

  const roomName = `room-${Math.floor(roomCounter / 2)}`;
  socket.join(roomName);

  if (!rooms[roomName]) {
    rooms[roomName] = {
      ball: { x: 0, y: 0, vx: 0.1, vy: 0.1 }, // Ball position and velocity
      paddles: { paddle1: 0, paddle2: 0 },
      scores: { paddle1: 0, paddle2: 0 },
      gameOver: false,
    };
  }

  const paddleId = roomCounter % 2 === 0 ? "paddle1" : "paddle2";
  socket.emit("init", { roomName, paddleId });

  roomCounter++;

  socket.on("paddleMove", (data) => {
    if (rooms[roomName].gameOver) return;

    if (data.position > GAME_BOUNDS.x - PADDLE_WIDTH / 2) {
      data.position = GAME_BOUNDS.x - PADDLE_WIDTH / 2;
    }
    if (data.position < -GAME_BOUNDS.x + PADDLE_WIDTH / 2) {
      data.position = -GAME_BOUNDS.x + PADDLE_WIDTH / 2;
    }

    rooms[roomName].paddles[data.paddleId] = data.position;
    socket.to(roomName).emit("updatePaddle", data);
  });

  if (roomCounter % 2 === 0) {
    startBallMovement(roomName);
  }

  socket.on("disconnect", () => {
    console.log("A user disconnected");
  });
});

function startBallMovement(roomName) {
  const interval = setInterval(() => {
    const room = rooms[roomName];
    if (!room || room.gameOver) {
      clearInterval(interval);
      return;
    }

    const ball = room.ball;
    const paddles = room.paddles;
    const scores = room.scores;

    ball.x += ball.vx;
    ball.y += ball.vy;

    // Left and right wall collisions
    if (
      ball.x >= GAME_BOUNDS.x - BALL_RADIUS ||
      ball.x <= -GAME_BOUNDS.x + BALL_RADIUS
    ) {
      ball.vx *= -1; // Reverse direction
      ball.x =
        ball.x > 0 ? GAME_BOUNDS.x - BALL_RADIUS : -GAME_BOUNDS.x + BALL_RADIUS;
    }

    // Paddle 1 (bottom) collision
    const hitBottomPaddle =
      ball.y <= -GAME_BOUNDS.y + PADDLE_HEIGHT + BALL_RADIUS &&
      ball.x >= paddles.paddle1 - PADDLE_WIDTH / 2 &&
      ball.x <= paddles.paddle1 + PADDLE_WIDTH / 2;

    // Paddle 2 (top) collision
    const hitTopPaddle =
      ball.y >= GAME_BOUNDS.y - PADDLE_HEIGHT - BALL_RADIUS &&
      ball.x >= paddles.paddle2 - PADDLE_WIDTH / 2 &&
      ball.x <= paddles.paddle2 + PADDLE_WIDTH / 2;

    if (hitBottomPaddle || hitTopPaddle) {
      ball.vy *= -1; // Reverse vertical direction
      ball.y = hitBottomPaddle
        ? -GAME_BOUNDS.y + PADDLE_HEIGHT + BALL_RADIUS
        : GAME_BOUNDS.y - PADDLE_HEIGHT - BALL_RADIUS;

      console.log(
        `Collision detected! Ball: (${ball.x.toFixed(2)}, ${ball.y.toFixed(
          2
        )}), ` +
          `Paddle1: ${paddles.paddle1.toFixed(
            2
          )}, Paddle2: ${paddles.paddle2.toFixed(2)}`
      );
    }

    // Top and bottom wall collisions (score points)
    if (ball.y >= GAME_BOUNDS.y) {
      scores.paddle1++;
      io.to(roomName).emit("updateScores", scores);
      resetGame(roomName, "paddle1");
    } else if (ball.y <= -GAME_BOUNDS.y) {
      scores.paddle2++;
      io.to(roomName).emit("updateScores", scores);
      resetGame(roomName, "paddle2");
    }

    // Check for game over
    if (scores.paddle1 === WINNING_SCORE || scores.paddle2 === WINNING_SCORE) {
      room.gameOver = true;

      const winner = scores.paddle1 === WINNING_SCORE ? "paddle1" : "paddle2";
      io.to(roomName).emit("gameOver", { winner });
      console.log(`Game Over! Winner: ${winner}`);
      clearInterval(interval);
      return;
    }

    io.to(roomName).emit("updateBall", ball);
  }, 16); // 60 FPS
}

function resetGame(roomName, scorer) {
  const room = rooms[roomName];

  // 공과 패들 위치 초기화
  room.ball = { x: 0, y: 0, vx: 0, vy: 0 }; // 공 정지
  room.paddles.paddle1 = 0;
  room.paddles.paddle2 = 0;

  io.to(roomName).emit("resetPositions", {
    ball: room.ball,
    paddles: room.paddles,
  });

  // 1초 대기 후 공 재시작
  setTimeout(() => {
    const initialSpeed = 0.1;
    room.ball.vx = initialSpeed * (Math.random() > 0.5 ? 1 : -1); // 랜덤 X 방향
    room.ball.vy = scorer === "paddle1" ? initialSpeed : -initialSpeed; // 득점 반대 방향
    io.to(roomName).emit("updateBall", room.ball);
  }, 1000);
}

const PORT = 3000;
httpServer.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
