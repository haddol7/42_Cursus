const socket = io();

let scene, camera, renderer;
let paddle1, paddle2, ball, ballLight, walls, floor;
let paddleId;

const GAME_BOUNDS = { x: 5, y: 5 }; // 게임 경계
const paddleSpeed = 5; // 패들 속도 (초 단위)
let paddleDirection = 0; // 패들 이동 방향 (-1: 왼쪽, 1: 오른쪽)
const clock = new THREE.Clock(); // 시간 계산을 위한 Clock 객체

function init() {
  // Create scene
  scene = new THREE.Scene();
  scene.background = new THREE.Color(0x1a1a1a); // 어두운 회색 배경

  // Create camera
  camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);

  // 카메라 위치 및 시점 조정
  if (paddleId === 'paddle1') {
    camera.position.set(0, -7, 5); // 패들1이 아래쪽
    camera.lookAt(0, 0, 0);
  } else if (paddleId === 'paddle2') {
    camera.position.set(0, 7, 5); // 패들2가 아래쪽
    camera.lookAt(0, 0, 0);
    camera.rotation.z = Math.PI; // 화면을 180도 회전
  }

  // Create renderer
  renderer = new THREE.WebGLRenderer({ antialias: true });
  renderer.setSize(window.innerWidth, window.innerHeight);
  renderer.shadowMap.enabled = true; // 그림자 활성화
  renderer.physicallyCorrectLights = true; // 물리적으로 정확한 조명
  document.body.appendChild(renderer.domElement);

  window.addEventListener('resize', () => {
    // 카메라 종횡비 업데이트
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();

    // 렌더러 크기 업데이트
    renderer.setSize(window.innerWidth, window.innerHeight);
  });

  // Create paddles
  const paddleGeometry = new THREE.BoxGeometry(1, 0.2, 0.2);
  const paddleMaterial1 = new THREE.MeshStandardMaterial({ color: 0x00ff00 });
  const paddleMaterial2 = new THREE.MeshStandardMaterial({ color: 0x0000ff });

  paddle1 = new THREE.Mesh(paddleGeometry, paddleMaterial1);
  paddle1.position.set(0, -4.5, 0.2); // 아래쪽 패들
  paddle1.castShadow = true; // 그림자 생성
  scene.add(paddle1);

  paddle2 = new THREE.Mesh(paddleGeometry, paddleMaterial2);
  paddle2.position.set(0, 4.5, 0.2); // 위쪽 패들
  paddle2.castShadow = true; // 그림자 생성
  scene.add(paddle2);

  // Create ball
  const ballGeometry = new THREE.SphereGeometry(0.2, 32, 32);
  const ballMaterial = new THREE.MeshStandardMaterial({
    color: 0xff0000,
    emissive: 0xff0000, // 공 자체의 발광 색상
    emissiveIntensity: 1.5, // 발광 강도
  });
  ball = new THREE.Mesh(ballGeometry, ballMaterial);
  ball.position.set(0, 0, 0.2);
  ball.castShadow = true; // 그림자 생성
  scene.add(ball);

  // Add floor
  addFloor();

  // Add light to the ball
  addBallLight();

  // Create walls (game boundaries)
  createWalls();

  // Add ambient light to the scene
  const ambientLight = new THREE.AmbientLight(0x404040, 0.5); // 부드러운 조명
  scene.add(ambientLight);

  // Add directional light for general lighting
  const directionalLight = new THREE.DirectionalLight(0xffffff, 0.7);
  directionalLight.position.set(0, 5, 10);
  directionalLight.castShadow = true; // 그림자 생성
  directionalLight.shadow.mapSize.width = 2048; // 그림자 해상도
  directionalLight.shadow.mapSize.height = 2048;
  directionalLight.shadow.camera.near = 0.1;
  directionalLight.shadow.camera.far = 25;
  scene.add(directionalLight);

  // Start animation
  animate();
}

function addFloor() {
  const floorGeometry = new THREE.PlaneGeometry(GAME_BOUNDS.x * 2, GAME_BOUNDS.y * 2);

  // MeshStandardMaterial로 반사 효과 설정
  const floorMaterial = new THREE.MeshStandardMaterial({
    color: 0x222222, // 바닥 기본 색상
    roughness: 0.5,  // 표면 거칠기 (낮을수록 반사도가 높음)
    metalness: 0.8,  // 금속성 (높을수록 반사도가 강해짐)
  });

  floor = new THREE.Mesh(floorGeometry, floorMaterial);
  floor.receiveShadow = true; // 바닥에서 그림자를 받도록 설정
  scene.add(floor);
}

function addBallLight() {
  ballLight = new THREE.PointLight(0xffffff, 10, 15); // 붉은 조명, 밝기, 범위
  ballLight.position.set(0, 0, 0.5); // 초기 공 위치와 동일
  ballLight.castShadow = true; // 그림자 활성화
  scene.add(ballLight);
}

function createWalls() {
  const wallMaterial = new THREE.LineBasicMaterial({ color: 0xffffff }); // 하얀색 선
  const points = [
    new THREE.Vector3(-GAME_BOUNDS.x, GAME_BOUNDS.y, 0), // Top-left
    new THREE.Vector3(GAME_BOUNDS.x, GAME_BOUNDS.y, 0), // Top-right
    new THREE.Vector3(GAME_BOUNDS.x, -GAME_BOUNDS.y, 0), // Bottom-right
    new THREE.Vector3(-GAME_BOUNDS.x, -GAME_BOUNDS.y, 0), // Bottom-left
    new THREE.Vector3(-GAME_BOUNDS.x, GAME_BOUNDS.y, 0), // Close the loop
  ];
  const wallGeometry = new THREE.BufferGeometry().setFromPoints(points);
  walls = new THREE.LineLoop(wallGeometry, wallMaterial);
  scene.add(walls);
}

function animate() {
  requestAnimationFrame(animate);

  // 프레임 간 시간 차이 계산
  const deltaTime = clock.getDelta();

  // 공의 조명 위치 업데이트
  ballLight.position.set(ball.position.x, ball.position.y, ball.position.z);

  // 패들 움직임 처리
  if (paddleId === 'paddle1') {
    paddle1.position.x += paddleDirection * paddleSpeed * deltaTime;
    paddle1.position.x = Math.max(
      Math.min(paddle1.position.x, GAME_BOUNDS.x - 0.5),
      -GAME_BOUNDS.x + 0.5
    );
    socket.emit('paddleMove', { paddleId, position: paddle1.position.x });
  } else if (paddleId === 'paddle2') {
    paddle2.position.x += paddleDirection * paddleSpeed * deltaTime;
    paddle2.position.x = Math.max(
      Math.min(paddle2.position.x, GAME_BOUNDS.x - 0.5),
      -GAME_BOUNDS.x + 0.5
    );
    socket.emit('paddleMove', { paddleId, position: paddle2.position.x });
  }

  renderer.render(scene, camera);
}

socket.on('updatePaddle', (data) => {
  if (data.paddleId === 'paddle1') {
    paddle1.position.x = data.position;
  } else if (data.paddleId === 'paddle2') {
    paddle2.position.x = data.position;
  }
});

socket.on('updateBall', (ballData) => {
  ball.position.set(ballData.x, ballData.y, 0.2);
});

socket.on('init', (data) => {
  paddleId = data.paddleId;
  console.log(`You are controlling ${paddleId}`);
  init();
});

const keyState = { left: false, right: false };

window.addEventListener('keydown', (event) => {
  if (event.key === 'ArrowLeft') {
    keyState.left = true;
  } else if (event.key === 'ArrowRight') {
    keyState.right = true;
  }
  updatePaddleDirection();
});

window.addEventListener('keyup', (event) => {
  if (event.key === 'ArrowLeft') {
    keyState.left = false;
  } else if (event.key === 'ArrowRight') {
    keyState.right = false;
  }
  updatePaddleDirection();
});

function updatePaddleDirection() {
  if (keyState.left && !keyState.right) {
    paddleDirection = -1;
  } else if (keyState.right && !keyState.left) {
    paddleDirection = 1;
  } else {
    paddleDirection = 0;
  }
}
