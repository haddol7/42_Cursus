import * as THREE from "three";
import { EffectComposer } from "three/addons/postprocessing/EffectComposer.js";
import { RenderPass } from "three/addons/postprocessing/RenderPass.js";
import { UnrealBloomPass } from "three/addons/postprocessing/UnrealBloomPass.js";

export function initScene(paddleId) {
  const scene = new THREE.Scene();
  scene.background = new THREE.Color(0x000000);

  const camera = new THREE.PerspectiveCamera(
    75,
    window.innerWidth / window.innerHeight,
    0.1,
    1000
  );

  // 카메라 위치 설정
  if (paddleId === "paddle1") {
    camera.position.set(0, -9.5, 4);
    camera.lookAt(0, 0, 0);
  } else if (paddleId === "paddle2") {
    camera.position.set(0, 9.5, 4);
    camera.lookAt(0, 0, 0);
    camera.rotation.z = Math.PI;
  }

  // 렌더러 설정
  const renderer = new THREE.WebGLRenderer({ antialias: true });
  renderer.setSize(window.innerWidth, window.innerHeight);
  renderer.shadowMap.enabled = true;
  renderer.physicallyCorrectLights = true;
  document.body.appendChild(renderer.domElement);

  // Postprocessing 설정 - 블룸 효과
  const composer = new EffectComposer(renderer);
  composer.addPass(new RenderPass(scene, camera));
  composer.addPass(
    new UnrealBloomPass(
      new THREE.Vector2(window.innerWidth, window.innerHeight),
      2.5,
      1,
      0.1
    )
  );
  return { scene, camera, renderer, composer };
}

export function onWindowResize(camera, renderer, composer) {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
  composer.setSize(window.innerWidth, window.innerHeight);
}
