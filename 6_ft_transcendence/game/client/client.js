import { initScene, onWindowResize } from "./sceneSetup.js";
import { createGeometry } from "./geometrySetup.js";
import { animate } from "./animation.js";
import { updateScore } from "./scoreboard.js";

const socket = io();
let paddleId;
let player1Score = 0;
let player2Score = 0;

socket.on("init", (data) => {
  paddleId = data.paddleId;
  console.log(`You are controlling ${paddleId}`);

  //three.js 오브젝트, 점수판 초기화
  const { scene, camera, renderer, composer } = initScene(paddleId);
  createGeometry(scene);
  updateScore(scene, player1Score, player2Score);

  // socket.io 이벤트 처리
  setupSocketEvents(socket, scene);

  //화면 크기 조절
  window.addEventListener("resize", () => {
    onWindowResize(camera, renderer, composer);
  });

  animate(scene, camera, composer, socket, paddleId);
});

function setupSocketEvents(socket, scene) {
  socket.on("updatePaddle", (data) => {
    const paddle = scene.getObjectByName(data.paddleId);
    if (paddle) paddle.position.x = data.position;
  });

  socket.on("updateBall", (ballData) => {
    const ball = scene.getObjectByName("ball");
    ball.position.set(ballData.x, ballData.y, 0.2);
  });

  socket.on("updateScore", (scores) => {
    player1Score = scores.paddle1;
    player2Score = scores.paddle2;
    updateScore(scene, player1Score, player2Score);
  });

  socket.on("resetPositions", (data) => {
    const paddle1 = scene.getObjectByName("paddle1");
    const paddle2 = scene.getObjectByName("paddle2");
    const ball = scene.getObjectByName("ball");

    paddle1.position.x = 0;
    paddle2.position.x = 0;
    ball.position.set(0, 0, 0.2);
  });
}
