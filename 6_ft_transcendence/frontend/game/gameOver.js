export function showGameOver(winner, paddle1, paddle2, nextOpponent) {
  const gameOverPopup = document.getElementById("gameOverPopup");
  const gameResult = document.getElementById("gameResult");
  const restartButton = document.getElementById("restartButton");

  // nextOpponent에 따라 UI 동적 변경
  gameResult.innerHTML = `
  <div style="font-size: 48px; font-weight: 700; margin-bottom: 20px; color: ${
    winner ? "rgb(0, 255, 50)" : "rgb(255, 0, 50)"
  };">
    ${winner ? "YOU WIN!" : "YOU LOSE"}
  </div>

  <div style="display: inline-block; padding: 10px 20px; background-color: ${
    winner ? "rgb(0, 255, 50)" : "rgb(255, 0, 50)"
  }; border-radius: 10px; font-size: 24px; color: #fff; margin-bottom: 30px;">
    ${paddle1} : ${paddle2}
  </div>

  ${
    nextOpponent !== "END"
      ? `
      <div style="margin-top: 30px; text-align: center;">
        <div style="font-size: 20px; font-weight: 600; margin-bottom: 10px; color: #333;">
          🎯 다음 상대 🎯
        </div>
        <div style="font-size: 28px; font-weight: 700; color: rgb(173, 216, 230);">
          ${nextOpponent}
        </div>
      </div>
    `
      : ""
  }
`;

  gameOverPopup.style.display = "flex";

  if (nextOpponent === "END") {
    setButtonText("나가기");
  } else {
    setButtonText("다음 게임");
  }

  // 버튼 스타일 동적 적용 (초기 설정)
  restartButton.style.padding = "20px 40px";
  restartButton.style.fontSize = "24px";
  restartButton.style.borderRadius = "15px";
  restartButton.style.cursor = "pointer";
  restartButton.style.backgroundColor = "rgb(153, 204, 255)";
  restartButton.style.color = "#fff";
  restartButton.style.border = "none";
  restartButton.style.boxShadow = "0 6px 10px rgba(0, 0, 0, 0.3)";

  // 버튼 텍스트 변경 함수
  function setButtonText(newText) {
    document.getElementById("restartButton").textContent = newText;
  }

  // 초기 설정
  setButtonText("나가기");
}
