import {
  renderNavBar,
  bindEventToNavBar,
  clearBody,
  clearExceptNavBar,
} from "./lowRankElements.mjs";
import { GameQueueCreationPage } from "./gameQueueCreation.mjs";
import { GameQueuePage } from "./gameQueue.mjs";
import { PageManager } from "./manager.mjs";
import { RoomSocketManager } from "../socketManager.mjs";
import { AIMatchPage } from "./aiMatch.mjs";

export class GameLobbyPage {
  static render() {
    renderNavBar();

    document.body.innerHTML += `
    <div id="gameLobbySection">
      <div id="gameRoomList" class="box">
      </div>
      <a id="gameQueueCreationLink" class="nav justify-content-center link">Make New Game Room</a>
      <a id="aiMatchLink" class="nav justify-content-center link">Match With AI</a>
    </div>
    `;

    bindEventToNavBar();

    document
      .getElementById("gameQueueCreationLink")
      .addEventListener("click", (event) => {
        event.preventDefault();
        clearExceptNavBar();
        GameQueueCreationPage.render();
      });

    document
      .getElementById("aiMatchLink")
      .addEventListener("click", (event) => {
        event.preventDefault();
        clearBody();
        RoomSocketManager.disconnect();
        AIMatchPage.play();
      });

    PageManager.currentpageStatus = PageManager.pageStatus.gameLobby;

    RoomSocketManager.connect();
  }

  static renderAndPushHistory() {
    GameLobbyPage.render();
    history.pushState(PageManager.pageStatus.gameLobby, "");
  }

  static destroy() {
    const gameLobbySection = document.getElementById("gameLobbySection");
    gameLobbySection.innerHTML = "";
    gameLobbySection.parentNode.removeChild(gameLobbySection);
  }

  static updateGameRoomList = (roomList) => {
    if (roomList === null) {
      return;
    }

    let gameRoomList = document.getElementById("gameRoomList");
    gameRoomList.innerHTML = "";

    roomList.room.forEach((value) => {
      const gameQueue = document.createElement("div");
      gameQueue.classList.add("box");
      gameQueue.innerHTML = `
        <div class="oneToOneRatioWrapher">
          <h6 class="leftAlignedTitle">room id : </h6>
          <p class="paragraph">${value.room_id}</p>
        </div>
        <div class="oneToOneRatioWrapher">
          <h6 class="leftAlignedTitle">room name : </h6>
          <p class="paragraph">${value.room_name}</p>
        </div>
        <div class="oneToOneRatioWrapher">
          <h6 class="leftAlignedTitle">room limit : </h6>
          <p class="paragraph">${value.room_limit}</p>
        </div>
        <div class="oneToOneRatioWrapher">
          <h6 class="leftAlignedTitle">current number of members : </h6>
          <p class="paragraph">${value.room_cur_people}</p>
        </div>
      `;
      gameRoomList.appendChild(gameQueue);

      const enterQueue = document.createElement("a");
      enterQueue.classList.add(..."link".split(" "));
      enterQueue.textContent = "enter Queue";
      gameQueue.appendChild(enterQueue);

      enterQueue.addEventListener("click", () => {
        clearExceptNavBar();
        RoomSocketManager.maxNumOfParticipant = Number(value.room_limit);
        GameQueuePage.render();
        RoomSocketManager.emitEnterRoom(value.room_id);
      });
    });
  };
}
