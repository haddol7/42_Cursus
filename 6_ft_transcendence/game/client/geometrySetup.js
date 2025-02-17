import * as THREE from "three";

export function createGeometry(scene) {
  const GAME_BOUNDS = { x: 5, y: 7 };

  // Paddle 설정
  const paddleGeometry = new THREE.BoxGeometry(1, 0.2, 0.2);
  const paddleEdgesMaterial = new THREE.LineBasicMaterial({ color: 0x00ff00 });

  const paddle1Edges = new THREE.LineSegments(
    new THREE.EdgesGeometry(paddleGeometry),
    paddleEdgesMaterial
  );
  paddle1Edges.name = "paddle1";
  paddle1Edges.position.set(0, -GAME_BOUNDS.y + 0.5, 0.2);
  scene.add(paddle1Edges);

  const paddle2Edges = new THREE.LineSegments(
    new THREE.EdgesGeometry(paddleGeometry),
    new THREE.LineBasicMaterial({ color: 0x0000ff })
  );
  paddle2Edges.name = "paddle2";
  paddle2Edges.position.set(0, GAME_BOUNDS.y - 0.5, 0.2);
  scene.add(paddle2Edges);

  // Ball 설정
  const ballGeometry = new THREE.IcosahedronGeometry(0.3);
  const ballEdgesMaterial = new THREE.LineBasicMaterial({ color: 0xff0000 });

  const ballEdges = new THREE.LineSegments(
    new THREE.EdgesGeometry(ballGeometry),
    ballEdgesMaterial
  );
  ballEdges.name = "ball";
  ballEdges.position.set(0, 0, 0.2);
  ballEdges.vel = 0;
  scene.add(ballEdges);

  // 바닥 설정
  const floorGeometry = new THREE.PlaneGeometry(
    GAME_BOUNDS.x * 2,
    GAME_BOUNDS.y * 2
  );
  const floorEdgesMaterial = new THREE.LineBasicMaterial({ color: 0xffffff });

  const floorEdges = new THREE.LineSegments(
    new THREE.EdgesGeometry(floorGeometry),
    floorEdgesMaterial
  );
  floorEdges.position.set(0, 0, 0);
  scene.add(floorEdges);

  // 벽 설정
  let height = 0.7;

  const wallMaterial = new THREE.LineBasicMaterial({ color: 0xffffff });
  const points = [
    new THREE.Vector3(-GAME_BOUNDS.x, GAME_BOUNDS.y, height),
    new THREE.Vector3(GAME_BOUNDS.x, GAME_BOUNDS.y, height),
    new THREE.Vector3(GAME_BOUNDS.x, -GAME_BOUNDS.y, height),
    new THREE.Vector3(-GAME_BOUNDS.x, -GAME_BOUNDS.y, height),
    new THREE.Vector3(-GAME_BOUNDS.x, GAME_BOUNDS.y, height),
  ];
  const wallGeometry = new THREE.BufferGeometry().setFromPoints(points);
  const walls = new THREE.LineLoop(wallGeometry, wallMaterial);
  scene.add(walls);

  // 벽 선 설정
  const segmentsMaterial = new THREE.LineBasicMaterial({ color: 0xffffff });
  const segmentsPoints = [
    new THREE.Vector3(GAME_BOUNDS.x, GAME_BOUNDS.y, 0),
    new THREE.Vector3(GAME_BOUNDS.x, GAME_BOUNDS.y, height),
    new THREE.Vector3(-GAME_BOUNDS.x, GAME_BOUNDS.y, 0),
    new THREE.Vector3(-GAME_BOUNDS.x, GAME_BOUNDS.y, height),
    new THREE.Vector3(GAME_BOUNDS.x, -GAME_BOUNDS.y, 0),
    new THREE.Vector3(GAME_BOUNDS.x, -GAME_BOUNDS.y, height),
    new THREE.Vector3(-GAME_BOUNDS.x, -GAME_BOUNDS.y, 0),
    new THREE.Vector3(-GAME_BOUNDS.x, -GAME_BOUNDS.y, height),
    new THREE.Vector3(GAME_BOUNDS.x, 0, 0),
    new THREE.Vector3(-GAME_BOUNDS.x, 0, 0),
  ];
  const segmentsGeometry = new THREE.BufferGeometry().setFromPoints(
    segmentsPoints
  );
  const segments = new THREE.LineSegments(segmentsGeometry, segmentsMaterial);
  scene.add(segments);

  // 경기장 원 초기화
  const ringGeometry = new THREE.RingGeometry(2);
  const edges = new THREE.EdgesGeometry(ringGeometry);
  const lineMaterial = new THREE.LineBasicMaterial({ color: 0xffffff });
  const ringOutline = new THREE.LineSegments(edges, lineMaterial);
  ringOutline.position.set(0, 0, 0);
  scene.add(ringOutline);

  // 지평선 초기화
  const ringGeometry1 = new THREE.RingGeometry(100);
  const edges1 = new THREE.EdgesGeometry(ringGeometry1);
  const lineMaterial1 = new THREE.LineBasicMaterial({ color: 0xffffff });
  const ringOutline1 = new THREE.LineSegments(edges1, lineMaterial1);
  ringOutline1.position.set(0, 0, 0);
  scene.add(ringOutline1);
}
