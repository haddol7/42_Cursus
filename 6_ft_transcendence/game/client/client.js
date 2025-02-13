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

// 디버그 : 방 번호 및 AI 모드 설정
let DEBUG_ROOM_ID = 4242;
const DEBUG_AI = false;
let DEBUG_NEXT_OPPONENT = "TEST";

let keyDownHandler;
let keyUpHandler;

let scene, camera, renderer, composer;

// 게임 시작 함수
function initGame() {
  socket = io();

  socket.on("requestRoomId", () => {
    socket.emit("roomId", { roomId: DEBUG_ROOM_ID, isAIMode: DEBUG_AI });
  });

  keyDownHandler = (event) => handleKeyDown(event, paddleId);
  keyUpHandler = (event) => handleKeyUp(event, paddleId);
  window.addEventListener("keydown", keyDownHandler);
  window.addEventListener("keyup", keyUpHandler);

  socket.on("init", (data) => {
    paddleId = data.paddleId;
    ({ scene, camera, renderer, composer } = initScene(paddleId));
    createGeometry(scene);
    animate(scene, camera, composer, socket, paddleId);

    updateScore(scene, player1Score, player2Score, paddleId);
    handleSocketEvents(socket, scene);

    window.addEventListener("resize", () => {
      onWindowResize(camera, renderer, composer);
    });
  });

  socket.on("disconnect", (reason) => {
    console.log("서버와의 연결이 종료되었습니다.", reason);
    alert(reason);
  });
}

// nextGame 이벤트가 들어갈 함수
// TODO : socket.io nextGame 함수 추가
function restartGame() {
  // 기존 애니메이션 중단
  stopAnimation();

  // 기존 소켓 연결 종료
  if (socket) {
    socket.off();
    socket.disconnect();
  }

  // 디버그 : 방 번호 증가
  // TODO : nextGame에서 어떻게 동작하는지 보고 수정
  DEBUG_ROOM_ID += 1;
  if (DEBUG_ROOM_ID === 4244) {
    console.log("DEBUG_ROOM_ID is 4244");
    DEBUG_NEXT_OPPONENT = "END";
  }

  socket = io();
  socket.on("requestRoomId", () => {
    socket.emit("roomId", { roomId: DEBUG_ROOM_ID, isAIMode: DEBUG_AI });
  });

  socket.on("init", (data) => {
    paddleId = data.paddleId;

    // 이벤트 제거 및 재등록
    if (keyDownHandler) window.removeEventListener("keydown", keyDownHandler);
    if (keyUpHandler) window.removeEventListener("keyup", keyUpHandler);
    keyDownHandler = (event) => handleKeyDown(event, paddleId);
    keyUpHandler = (event) => handleKeyUp(event, paddleId);
    window.addEventListener("keydown", keyDownHandler);
    window.addEventListener("keyup", keyUpHandler);

    resetGameObjects();

    // ✅ 새로운 애니메이션 실행
    animate(scene, camera, composer, socket, paddleId);
  });

  gameOverPopup.style.display = "none";
}

// ✅ 오브젝트(카메라, 점수판, 공과 패들) 위치 초기화 함수
function resetGameObjects() {
  const paddle1 = scene.getObjectByName("paddle1");
  const paddle2 = scene.getObjectByName("paddle2");
  const ball = scene.getObjectByName("ball");

  if (paddle1) paddle1.position.set(0, -6.5, 0.2);
  if (paddle2) paddle2.position.set(0, 6.5, 0.2);
  if (ball) {
    ball.position.set(0, 0, 0.2);
    ball.vel = 0; // 속도 초기화
  }

  player1Score = 0;
  player2Score = 0;
  updateScore(scene, player1Score, player2Score, paddleId);
  handleSocketEvents(socket, scene);

  if (paddleId === "paddle1") {
    camera.position.set(0, -10.5, 3);
    camera.lookAt(0, 0, 1);
  } else if (paddleId === "paddle2") {
    camera.position.set(0, 10.5, 3);
    camera.lookAt(0, 0, 1);
    camera.rotation.z = Math.PI;
  }
}

// 버튼 클릭 시 게임 재시작
restartButton.addEventListener("click", () => {
  if (restartButton.textContent === "나가기") {
    // 뒤로 가기 동작
    window.history.back();
  } else if (restartButton.textContent === "다음 게임") {
    // 다음 게임 시작
    restartGame();
  }
});

// 최초 게임 실행
initGame();

function handleSocketEvents(socket, scene) {
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

  socket.on("resetPositions", resetGameObjects);

  socket.on("gameOver", (data) => {
    showGameOver(
      data.winner === paddleId,
      data.paddle1,
      data.paddle2,
      DEBUG_NEXT_OPPONENT
    );
  });
}
