import {
  renderNavBar,
  bindEventToNavBar,
  clearBody,
} from "./lowRankElements.mjs";
import { GameQueueCreationPage } from "./gameQueueCreation.mjs";
import { GameQueuePage } from "./gameQueue.mjs";
import { PageManager } from "./manager.mjs";
import { SocketManager } from "../socketManager.mjs";

export class GameLobbyPage {
  static render() {
    renderNavBar();

    document.body.innerHTML += `
      <div id="gameLobbySection" style="border: 1px solid gray; margin: 4px;">
        <div>
          <a id="gameQueueCreationLink" class="btn btn-info mb-3" style="margin: 4px;">make new game queue</a>
        </div>
        <div id="gameQueueList">
        </div>
      </div>
    `;

    bindEventToNavBar();

    const gameQueueCreationLink = document.getElementById(
      "gameQueueCreationLink"
    );
    gameQueueCreationLink.addEventListener("click", (event) => {
      event.preventDefault();
      clearBody();
      GameQueueCreationPage.render();
    });

    PageManager.currentpageStatus = PageManager.pageStatus.gameLobby;

    try {
      SocketManager.connect();
    } catch (e) {
      console.error(e);
    }
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

  static updateGameLobbySection = (roomList) => {
    if (roomList === null) return;

    let gameQueueList = document.getElementById("gameQueueList");
    gameQueueList.innerHTML = "";
    gameQueueList.style = "border: 1px solid gray; margin: 4px;";

    roomList.room.forEach((value) => {
      const gameQueue = document.createElement("div");
      gameQueue.style = "border: 1px solid gray; margin: 4px;";
      gameQueue.textContent = `
      room id : ${value.room_id}\n
      room name : ${value.room_name}\n
      room limit : ${value.room_limit}\n
      current number of members : ${value.room_cur_people}\n`;
      gameQueueList.appendChild(gameQueue);

      const enterQueue = document.createElement("a");
      enterQueue.classList.add(..."btn btn-info mb-3".split(" "));
      enterQueue.style = "margin: 4px;";
      enterQueue.textContent = "enter Queue";
      gameQueue.appendChild(enterQueue);

      enterQueue.addEventListener("click", () => {
        clearBody();
        console.log(`room name : ${value.room_name}, room limit : ${value.room_limit}`);
        SocketManager.emitEnterRoom(value.room_name);
        SocketManager.maxNumOfParticipant = value.room_limit;
        GameQueuePage.render();
      });
    });
  };
}
