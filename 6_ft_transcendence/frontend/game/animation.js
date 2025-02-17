import * as THREE from "three";

let shouldAnimate = true; // 애니메이션 실행 여부 플래그
let keyState = {};
let paddleDirection = 0;

export function handleKeyDown(event, paddleId) {
  if (event.key === "ArrowLeft")
    paddleDirection = paddleId === "paddle2" ? 1 : -1;
  else if (event.key === "ArrowRight")
    paddleDirection = paddleId === "paddle2" ? -1 : 1;

  keyState[event.key] = true;
}

export function handleKeyUp(event, paddleId) {
  keyState[event.key] = false;

  if (event.key === "ArrowRight") {
    paddleDirection = keyState["ArrowLeft"]
      ? paddleId === "paddle2"
        ? 1
        : -1
      : 0;
  } else if (event.key === "ArrowLeft") {
    paddleDirection = keyState["ArrowRight"]
      ? paddleId === "paddle2"
        ? -1
        : 1
      : 0;
  }
}

export function animate(scene, camera, composer, socket, paddleId) {
  shouldAnimate = true; // 애니메이션 시작
  const clock = new THREE.Clock();

  const starCount = 500;
  const starGeometry = new THREE.BufferGeometry();
  const positions = new Float32Array(starCount * 3);

  for (let i = 0; i < starCount; i++) {
    const x = (Math.random() - 0.5) * 1000;
    const y = (Math.random() - 0.5) * 1000 - 500;
    const z = (Math.random() - 0.2) * 1000;
    positions.set([x, y, z], i * 3);
  }

  starGeometry.setAttribute(
    "position",
    new THREE.BufferAttribute(positions, 3)
  );

  const starMaterial = new THREE.PointsMaterial({
    color: 0xffffff,
    size: 3,
    sizeAttenuation: true,
  });

  const stars = new THREE.Points(starGeometry, starMaterial);
  scene.add(stars);

  function update() {
    if (!shouldAnimate) {
      scene.remove(stars);
      return; // 애니메이션 중단 체크
    }
    requestAnimationFrame(update);
    const deltaTime = clock.getDelta();

    const ball = scene.getObjectByName("ball");
    if (ball) {
      ball.rotation.x += 5 * deltaTime;
      ball.rotation.y += 5 * deltaTime;
      ball.vel += 0.1 * deltaTime;
      ball.vel = Math.min(ball.vel, 3);
    }

    const paddle = scene.getObjectByName(paddleId);
    if (paddle && paddleDirection !== 0) {
      console.log(paddleId, paddleDirection);
      socket.emit("paddleMove", { paddleId, paddleDirection });
    }

    const starPositions = stars.geometry.attributes.position.array;
    let starVelocity = ball.vel * 10;
    if (isNaN(starVelocity) || starVelocity < 1) {
      starVelocity = 2;
    }
    for (let i = 0; i < starCount * 3; i += 3) {
      starPositions[i + 1] += 50 * deltaTime * starVelocity;
      if (starPositions[i + 1] > 600) {
        starPositions[i + 1] = (Math.random() - 0.5) * 1000 - 500;
      }
    }
    stars.geometry.attributes.position.needsUpdate = true;
    composer.render();
  }

  update();
}

// 애니메이션 중단 함수
export function stopAnimation() {
  shouldAnimate = false;
}
