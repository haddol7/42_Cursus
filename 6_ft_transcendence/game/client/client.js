import { initScene, onWindowResize } from "./sceneSetup.js";
import { createGeometry } from "./geometrySetup.js";
import { animate } from "./animation.js";
import { updateScore } from "./scoreboard.js";
import { showGameOver } from "./gameOver.js";

const socket = io();

let paddleId;
let player1Score = 0;
let player2Score = 0;

// 여기서 디버깅용으로 roomId를 설정할 수 있습니다.
const DEBUG_ROOMCODE = "4242";
const DEBUG_AI = true;
// 미사용
const DEBUG_PLAYERNAME = "daeha";

// 서버로부터 roomId를 요청받았을 때 roomId를 전송
socket.on("requestRoomId", () => {
  socket.emit("roomId", { roomId: DEBUG_ROOMCODE, isAIMode: DEBUG_AI });
});

// 서버에게 paddleId를 할당 받은 뒤, three.js 및 게임 초기화
socket.on("init", (data) => {
  paddleId = data.paddleId;

  // three.js 오브젝트, 점수판 초기화
  const { scene, camera, renderer, composer } = initScene(paddleId);
  createGeometry(scene);
  updateScore(scene, player1Score, player2Score);

  // socket.io 이벤트 처리
  handleSocketEvents(socket, scene);

  // 화면 크기 조절
  window.addEventListener("resize", () => {
    onWindowResize(camera, renderer, composer);
  });

  // paddle 이동 처리 및 애니메이션
  animate(scene, camera, composer, socket, paddleId);
});

// 연결 종료 이벤트 감지
socket.on("disconnect", (reason) => {
  console.log("서버와의 연결이 종료되었습니다.", reason);
  alert(reason);
});

function handleSocketEvents(socket, scene) {
  // 상대편 paddle 이동
  socket.on("updatePaddle", (data) => {
    const paddle = scene.getObjectByName(data.paddleId);
    if (paddle) paddle.position.x = data.position;
  });

  // 디버그  : AI 시점 공 이동 (1초 마다 리프레쉬)
  //   let lastUpdateTime = 0;

  //   socket.on("updateBall", (ballData) => {
  //     const currentTime = Date.now();
  //     if (paddleId !== "spectator" && currentTime - lastUpdateTime < 1000) {
  //       return;
  //     }
  //     lastUpdateTime = currentTime;

  //     const ball = scene.getObjectByName("ball");
  //     if (ball) {
  //       ball.position.set(ballData.x, ballData.y, 0.2);
  //     }
  //   });
  //

  socket.on("updateBall", (ballData) => {
    const ball = scene.getObjectByName("ball");
    ball.position.set(ballData.x, ballData.y, 0.2);
  });

  // 점수 변경
  socket.on("updateScore", (scores) => {
    player1Score = scores.paddle1;
    player2Score = scores.paddle2;
    updateScore(scene, player1Score, player2Score);
  });

  // 위치 초기화
  socket.on("resetPositions", () => {
    const paddle1 = scene.getObjectByName("paddle1");
    const paddle2 = scene.getObjectByName("paddle2");
    const ball = scene.getObjectByName("ball");

    paddle1.position.set(0, -6.5, 0.2);
    paddle2.position.set(0, 6.5, 0.2);
    ball.position.set(0, 0, 0.2);
  });

  // 게임 종료
  socket.on("gameOver", (data) => {
    showGameOver(data.winner === paddleId, data.paddle1, data.paddle2);
  });
}
