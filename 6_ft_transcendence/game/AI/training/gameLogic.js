const { rooms } = require("./roomManager");
const {
  GAME_BOUNDS,
  PADDLE_HEIGHT,
  PADDLE_WIDTH,
  WINNING_SCORE,
  BALL_SIZE,
  BALL_SPEED,
} = require("./constants");

function startBallMovement(roomName, io) {
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

    // 벽 충돌 및 반사
    if (
      ball.x >= GAME_BOUNDS.x - BALL_SIZE.x / 2 ||
      ball.x <= -GAME_BOUNDS.x + BALL_SIZE.x / 2
    ) {
      ball.vx *= -1.03;
      ball.x =
        ball.x > 0
          ? GAME_BOUNDS.x - BALL_SIZE.x / 2
          : -GAME_BOUNDS.x + BALL_SIZE.x / 2;
    }

    const hitTopPaddle =
      ball.y + BALL_SIZE.y / 2 >= GAME_BOUNDS.y - 0.5 - PADDLE_HEIGHT &&
      ball.x + BALL_SIZE.x / 2 >= paddles.paddle2 - PADDLE_WIDTH / 2 &&
      ball.x - BALL_SIZE.x / 2 <= paddles.paddle2 + PADDLE_WIDTH / 2;

    if (ball.y <= -GAME_BOUNDS.y + 0.9 || hitTopPaddle) {
      ball.vy *= -1.05;

      //옮길거
      if (Math.abs(ball.vy) > 0.2)
        ball.vy > 0 ? (ball.vy = 0.2) : (ball.vy = -0.2);
    }

    if (hitTopPaddle) io.to(roomName).emit("hitPaddle", { paddle: "paddle2" });

    //득점 체크
    if (ball.y >= GAME_BOUNDS.y - BALL_SIZE.y / 2) {
      scores.paddle1++;
      io.to(roomName).emit("updateScore", scores);
      resetGame(roomName, "paddle1", io);
    } else if (ball.y <= -GAME_BOUNDS.y + BALL_SIZE.y / 2) {
      scores.paddle2++;
      io.to(roomName).emit("updateScore", scores);
      resetGame(roomName, "paddle2", io);
    }

    // 게임 종료 체크
    if (scores.paddle1 === WINNING_SCORE || scores.paddle2 === WINNING_SCORE) {
      room.gameOver = true;
      const winner = scores.paddle1 === WINNING_SCORE ? "paddle1" : "paddle2";
      io.to(roomName).emit("gameOver", {
        winner,
        paddle1: scores.paddle1,
        paddle2: scores.paddle2,
      });
      clearInterval(interval);
    }

    ball.AI_pos = paddles.paddle2;
    io.to(roomName).emit("updateBall", ball);
  }, 16); // 60 FPS
}

function handlePaddleMove(roomName, data, io) {
  const room = rooms[roomName];
  if (!room) return;

  const { paddleId, paddleDirection } = data;

  //옮길 것 방향값을 0.075, -0.075로 고정. (클라 쪽에서 악의적으로 큰 값이 들어올 수 있음)
  let normalizedPaddleDirection;
  if (paddleDirection != 0) {
    normalizedPaddleDirection =
      (paddleDirection * 0.075) / Math.abs(paddleDirection);
  } else {
    // 방향값이 0이면 패들을 움직이지 않기에 return
    // 클라 쪽에서도 0이 들어오지 않을 것임
    return;
  }

  const position = room.paddles[paddleId] + normalizedPaddleDirection;
  room.paddles[paddleId] = Math.max(
    -GAME_BOUNDS.x + PADDLE_WIDTH / 2,
    Math.min(GAME_BOUNDS.x - PADDLE_WIDTH / 2, position)
  );

  io.to(roomName).emit("updatePaddle", {
    paddleId,
    position: room.paddles[paddleId],
  });
}

function resetGame(roomName, scorer, io) {
  const room = rooms[roomName];

  // 공과 패들 위치 초기화
  room.ball = { x: 0, y: 0, vx: 0, vy: 0 };
  room.paddles.paddle1 = 0;
  room.paddles.paddle2 = 0;

  io.to(roomName).emit("resetPositions", {});
  let rand = Math.random() - 0.5;
  if (Math.abs(rand) < 0.2) rand > 0 ? (rand = 0.2) : (rand = -0.2);
  room.ball.vx = BALL_SPEED * rand;
  room.ball.vy = scorer === "paddle1" ? BALL_SPEED : -BALL_SPEED;
}

module.exports = { startBallMovement, handlePaddleMove };
