import { initScene, onWindowResize } from "./sceneSetup.js";
import { createGeometry } from "./geometrySetup.js";
import {
  animate,
  stopAnimation,
  handleKeyDown,
  handleKeyUp,
} from "./animation.js";
import { updateScore } from "./scoreboard.js";
import { showGameOver } from "./gameOver.js";

const restartButton = document.getElementById("restartButton");
const gameOverPopup = document.getElementById("gameOverPopup");

let socket;
let paddleId;
let player1Score = 0;
let player2Score = 0;

let keyDownHandler;
let keyUpHandler;

let scene, camera, renderer, composer;

socket = io();
({ scene, camera, renderer, composer } = initScene(paddleId));
createGeometry(scene);

window.addEventListener("resize", () => {
  onWindowResize(camera, renderer, composer);
});

// 버튼 클릭 시 게임 재시작
restartButton.addEventListener("click", () => {
  if (restartButton.textContent === "나가기") {
    window.history.back(); // 뒤로가기
  } else if (restartButton.textContent === "다음 게임") {
    socket.emit("nextGame"); // 다음 게임 시작
    gameOverPopup.style.display = "none";
  }
});

handleSocketEvents(socket, scene);

function handleSocketEvents(socket, scene) {
  socket.on("init", (data) => {
    paddleId = data.paddleId;
    stopAnimation();
    if (keyDownHandler) window.removeEventListener("keydown", keyDownHandler);
    if (keyUpHandler) window.removeEventListener("keyup", keyUpHandler);
    keyDownHandler = (event) => handleKeyDown(event, paddleId);
    keyUpHandler = (event) => handleKeyUp(event, paddleId);
    window.addEventListener("keydown", keyDownHandler);
    window.addEventListener("keyup", keyUpHandler);
    resetGameObjects();
    animate(scene, camera, composer, socket, paddleId);
  });

  socket.on("updatePaddle", (data) => {
    const paddle = scene.getObjectByName(data.paddleId);
    if (paddle) paddle.position.x = data.position;
  });

  socket.on("updateBall", (ballData) => {
    const ball = scene.getObjectByName("ball");
    if (ball) {
      ball.position.set(ballData.x, ballData.y, 0.2);
    }
  });

  socket.on("updateScore", (scores) => {
    player1Score = scores.paddle1;
    player2Score = scores.paddle2;
    updateScore(scene, player1Score, player2Score, paddleId);
  });

  socket.on("resetPositions", resetPositions);

  socket.on("gameOver", (data) => {
    showGameOver(
      data.winner === paddleId,
      data.paddle1,
      data.paddle2,
      "data.opponents" // TODO : 해당 부분 백엔드 쪽에서 미구현
    );
  });

  socket.on("disconnect", (reason) => {
    console.log("서버와의 연결이 종료되었습니다.", reason);
    alert(reason);
  });
}

// 오브젝트(카메라, 점수판, 공과 패들) 초기화 함수 : 게임 시작할 때만 호출
function resetGameObjects() {
  resetPositions();
  updateScore(scene, 0, 0, paddleId);

  if (paddleId === "paddle1") {
    camera.position.set(0, -10.5, 3);
    camera.lookAt(0, 0, 1);
  } else if (paddleId === "paddle2") {
    camera.position.set(0, 10.5, 3);
    camera.lookAt(0, 0, 1);
    camera.rotation.z = Math.PI;
  }
}

// 패들, 공 위치 초기화 함수 : 점수판 업데이트 시 호출
function resetPositions() {
  const paddle1 = scene.getObjectByName("paddle1");
  const paddle2 = scene.getObjectByName("paddle2");
  const ball = scene.getObjectByName("ball");

  if (paddle1) paddle1.position.set(0, -6.5, 0.2);
  if (paddle2) paddle2.position.set(0, 6.5, 0.2);
  if (ball) {
    ball.position.set(0, 0, 0.2);
    ball.vel = 0;
  }
}
