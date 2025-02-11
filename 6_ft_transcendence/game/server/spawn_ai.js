const { spawn } = require("child_process");

const aiProcesses = new Map(); // 방별 AI 프로세스 관리

function spawnAI(roomCode) {
  if (aiProcesses.has(roomCode)) {
    console.log(`AI for room ${roomCode} is already running.`);
    return;
  }

  const aiProcess = spawn("python3", ["server/AI/AI_player.py", roomCode]);

  aiProcess.on("close", (code) => {
    aiProcesses.delete(roomCode); // 종료된 AI 프로세스 제거
  });

  aiProcesses.set(roomCode, aiProcess);
}

function stopAI(roomCode) {
  if (aiProcesses.has(roomCode)) {
    aiProcesses.get(roomCode).kill();
    aiProcesses.delete(roomCode);
  }
}

module.exports = { spawnAI, stopAI };
