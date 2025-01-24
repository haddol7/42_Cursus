import * as THREE from "three";
import { FontLoader } from "three/addons/loaders/FontLoader.js";
import { TextGeometry } from "three/addons/geometries/TextGeometry.js";

let player1Outline, player2Outline;
const FONT_SIZE = 3;

// 점수판 업데이트
export function updateScore(scene, player1Score, player2Score) {
  if (player1Outline !== 0 || player2Outline !== 0)
    scene.remove(player1Outline, player2Outline);

  const fontLoader = new FontLoader();
  fontLoader.load("/asset/pixelFont.json", (font) => {
    const outlineMaterial1 = new THREE.LineBasicMaterial({ color: 0x00ff00 });
    const outlineMaterial2 = new THREE.LineBasicMaterial({ color: 0x0000ff });

    const player1Geometry = new TextGeometry(
      `${player1Score} : ${player2Score}`,
      {
        font: font,
        size: FONT_SIZE,
        height: 0.1,
      }
    );
    player1Geometry.computeBoundingBox();
    const player1CenterOffset =
      (player1Geometry.boundingBox.max.x - player1Geometry.boundingBox.min.x) /
      2;

    const player1Edges = new THREE.EdgesGeometry(player1Geometry);
    player1Outline = new THREE.LineSegments(player1Edges, outlineMaterial1);
    player1Outline.position.set(-player1CenterOffset, 9, 4.5);
    player1Outline.rotation.x = Math.PI / 2;
    scene.add(player1Outline);

    const player2Geometry = new TextGeometry(
      `${player2Score} : ${player1Score}`,
      {
        font: font,
        size: FONT_SIZE,
        height: 0.1,
      }
    );
    player2Geometry.computeBoundingBox();
    const player2CenterOffset =
      (player2Geometry.boundingBox.max.x - player2Geometry.boundingBox.min.x) /
      2;

    const player2Edges = new THREE.EdgesGeometry(player2Geometry);
    player2Outline = new THREE.LineSegments(player2Edges, outlineMaterial2);
    player2Outline.position.set(player2CenterOffset, -9, 4.5);
    player2Outline.rotation.x = Math.PI / 2;
    player2Outline.rotation.y = Math.PI;
    scene.add(player2Outline);
  });
}
