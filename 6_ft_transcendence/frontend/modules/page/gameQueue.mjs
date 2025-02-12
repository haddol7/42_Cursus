import { renderNavBar } from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";
import { RoomSocketManager } from "../socketManager.mjs";
import { clearBody } from "./lowRankElements.mjs";
import { GameLobbyPage } from "./gamelobby.mjs";
import { TournamentPage } from "./tournament.mjs";

export class GameQueuePage {
  static render() {
    renderNavBar();

    document.body.innerHTML += `
    <div id="gameQueueSection" class = "box">
    </div>
    <a id="quitQueueLink" class="nav justify-content-center link">Quit queue link</a>
      `;

    const quitQueueLink = document.getElementById("quitQueueLink");
    quitQueueLink.addEventListener("click", (event) => {
      event.preventDefault();
      clearBody();
      RoomSocketManager.disconnect();
      GameLobbyPage.renderAndPushHistory();
    });

    PageManager.currentpageStatus = PageManager.pageStatus.gameQueue;
  }

  static updateQueueMemberSection = () => {
    const gameQueueSection = document.getElementById("gameQueueSection");
    gameQueueSection.innerHTML = "";

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
    gameQueueSection.appendChild(queueStatus);

    RoomSocketManager.participantList.people.forEach((value) => {
      console.log(`us id : ${value.user_id} us name : ${value.user_name}`);
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
      gameQueueSection.appendChild(participant);
    });

    if (
      RoomSocketManager.getNumOfParticipants() ===
      RoomSocketManager.maxNumOfParticipant
    ) {
      console.log("congraturation!!!");
      clearBody();

      TournamentPage.render();
    }
  };

  static destroy() {
    const gameQueueSection = document.getElementById("gameQueueSection");
    gameQueueSection.innerHTML = "";
    gameQueueSection.parentNode.removeChild(gameQueueSection);
  }
}
