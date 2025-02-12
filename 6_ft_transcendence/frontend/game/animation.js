import * as THREE from "three";

let keyState = {};

export function animate(scene, camera, composer, socket, paddleId) {
  let paddleDirection = 0;

  const clock = new THREE.Clock();

  // 별 생성
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

  // 키 입력 처리 (키 누름)
  window.addEventListener("keydown", (event) => {
    if (event.key === "ArrowLeft")
      paddleDirection = paddleId === "paddle2" ? 1 : -1;
    else if (event.key === "ArrowRight")
      paddleDirection = paddleId === "paddle2" ? -1 : 1;
    keyState[event.key] = true;
  });

  // 키 입력 처리 (키 뗌)
  window.addEventListener("keyup", (event) => {
    keyState[event.key] = false;

    if (event.key === "ArrowRight") {
      if (keyState["ArrowLeft"] === true) {
        paddleDirection = paddleId === "paddle2" ? 1 : -1;
      } else {
        paddleDirection = 0;
      }
    } else if (event.key === "ArrowLeft") {
      if (keyState["ArrowRight"] === true) {
        paddleDirection = paddleId === "paddle2" ? -1 : 1;
      } else {
        paddleDirection = 0;
      }
    }
  });

  function update() {
    requestAnimationFrame(update);
    const deltaTime = clock.getDelta();

    // 공 회전
    const ball = scene.getObjectByName("ball");
    if (ball) {
      ball.rotation.x += 5 * deltaTime;
      ball.rotation.y += 5 * deltaTime;
    }

    // 패들 움직임 처리
    const paddle = scene.getObjectByName(paddleId);
    if (paddle && paddleDirection !== 0) {
      // 패들 위치 전송
      socket.emit("paddleMove", { paddleId, paddleDirection });
    }

    // 별 위치 업데이트
    const starPositions = stars.geometry.attributes.position.array;
    // 공이 부딪힐수록 별이 더 빠르게 움직이도록 만들었습니다.
    let starVelocity = (Math.abs(ball.vx) * 4 + Math.abs(ball.vy) * 6) * 10;
    if (isNaN(starVelocity) || starVelocity < 1) {
      starVelocity = 2;
    }
    console.log(deltaTime, starVelocity);
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
