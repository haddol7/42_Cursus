import { runPongGame } from "../../game/client.js";
import { JWT } from "../authentication/jwt.mjs";
import { PageManager } from "./manager.mjs";
import { LOGIN_EXPIRED_MSG } from "../authentication/globalConstants.mjs";

export class AIMatchPage {
  static play = async () => {
    document.body.innerHTML = `
        <div id="gameOverPopup">
          <div id="popupContent">
            <h2>게임 종료!</h2>
            <p id="gameResult"></p>
            <button id="restartButton">나가기</button>
          </div>
        </div>
      `;

    const response = await fetch(
      "/api/game/ai",
      JWT.getOptionWithAccessToken("POST")
    );

    if (response.ok) runPongGame();
    else {
      const text = await response.text();
      if (response.status === 401 && text === "jwt.expired") {
        try {
          await JWT.getNewToken();
          await AIMatchPage.play();
        } catch (e) {
          alert(`${LOGIN_EXPIRED_MSG}(${e})`);
          logout();
        }
      } else alert(text);
    }

    PageManager.currentpageStatus = PageManager.pageStatus.aiMatch;
  };
}
