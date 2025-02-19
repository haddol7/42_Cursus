import { clearExceptNavBar, renderNavBar } from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";
import { RoomSocketManager } from "../socketManager.mjs";
import { clearBody } from "./lowRankElements.mjs";
import { GameLobbyPage } from "./gamelobby.mjs";
import { PongPage } from "./pong.mjs";

export class GameQueuePage {
  static render() {
    renderNavBar();

    document.body.innerHTML += `
    <div id="gameQueueSection">
      <div id="gameQueueInfo" class = "box">
      </div>
      <a id="quitQueueLink" class="nav justify-content-center link">Quit queue link</a>
    </div>
      `;

    const quitQueueLink = document.getElementById("quitQueueLink");
    quitQueueLink.addEventListener("click", (event) => {
      event.preventDefault();
      clearExceptNavBar();
      RoomSocketManager.disconnect();
      GameLobbyPage.renderAndPushHistory();
    });

    PageManager.currentpageStatus = PageManager.pageStatus.gameQueue;
  }

  static updateQueueInfo = () => {
    const gameQueueInfo = document.getElementById("gameQueueInfo");
    gameQueueInfo.innerHTML = "";

    const queueStatus = document.createElement("div");
    queueStatus.innerHTML = `
      <div class="oneToOneRatioWrapher">
        <h6 class="leftAlignedTitle">Current Number Of Member : </h6>
        <p class="paragraph">${RoomSocketManager.getNumOfParticipants()}</p>
      </div>
      <div class="oneToOneRatioWrapher">
        <h6 class="leftAlignedTitle">Max Number Of Member : </h6>
        <p class="paragraph">${RoomSocketManager.maxNumOfParticipant}</p>
      </div>
    `;
    gameQueueInfo.appendChild(queueStatus);

    RoomSocketManager.participantList.people.forEach((value) => {
      const participant = document.createElement("div");
      participant.classList.add("box");
      participant.innerHTML = `
        <div class="oneToOneRatioWrapher">
          <h6 class="leftAlignedTitle">user id : </h6>
          <p class="paragraph">${value.user_id}</p>
        </div>
        <div class="oneToOneRatioWrapher">
          <h6 class="leftAlignedTitle">user name : </h6>
          <p class="paragraph">${value.user_name}</p>
        </div>
      `;
      gameQueueInfo.appendChild(participant);
    });

    if (
      RoomSocketManager.getNumOfParticipants() ===
      RoomSocketManager.maxNumOfParticipant
    ) {
      clearBody();
      PongPage.play();
    }
  };

  static destroy() {
    const gameQueueSection = document.getElementById("gameQueueSection");
    gameQueueSection.innerHTML = "";
    gameQueueSection.parentNode.removeChild(gameQueueSection);
  }
}
