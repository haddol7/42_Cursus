import * as THREE from "three";
import { FontLoader } from "three/addons/loaders/FontLoader.js";
import { TextGeometry } from "three/addons/geometries/TextGeometry.js";

let fontCache = null;
const FONT_SIZE = 5;
const SCORE_TEXT_NAME = "scoreText";

const fontLoader = new FontLoader();
fontLoader.load("/asset/pixelFont.json", (font) => {
  fontCache = font; // 폰트 캐싱
});

// 점수판 업데이트 함수
export function updateScore(scene, player1Score, player2Score, paddleId) {
  // 기존 점수판 제거
  const oldText = scene.getObjectByName(SCORE_TEXT_NAME);
  if (oldText) {
    console.log("remove occured");
    scene.remove(oldText);
  }

  if (!fontCache) return; // 폰트가 아직 로드되지 않았다면 리턴

  const textString =
    paddleId === "paddle1"
      ? `${player1Score} : ${player2Score}`
      : `${player2Score} : ${player1Score}`;

  console.log(`paddleId : ${paddleId}`);
  console.log(`player1Score : ${player1Score}`);
  console.log(`player2Score : ${player2Score}`);
  const textGeometry = new TextGeometry(textString, {
    font: fontCache,
    size: FONT_SIZE,
    height: 0.1,
  });

  textGeometry.computeBoundingBox();
  const textCenterOffset =
    (textGeometry.boundingBox.max.x - textGeometry.boundingBox.min.x) / 2;

  const textEdges = new THREE.EdgesGeometry(textGeometry);
  const textMaterial = new THREE.LineBasicMaterial({
    color: paddleId === "paddle1" ? 0x00ff00 : 0x0000ff,
  });
  const textMesh = new THREE.LineSegments(textEdges, textMaterial);

  textMesh.name = SCORE_TEXT_NAME; // 점수판 이름 설정

  if (paddleId === "paddle1") {
    textMesh.position.set(-textCenterOffset, 9, 6);
    textMesh.rotation.x = Math.PI / 2;
  } else {
    textMesh.position.set(textCenterOffset, -9, 6);
    textMesh.rotation.x = Math.PI / 2;
    textMesh.rotation.y = Math.PI;
  }

  scene.add(textMesh);
}
