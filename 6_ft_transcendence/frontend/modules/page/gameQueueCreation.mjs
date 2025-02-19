import { clearExceptNavBar, renderNavBar } from "./lowRankElements.mjs";
import { GameQueuePage } from "./gameQueue.mjs";
import { PageManager } from "./manager.mjs";
import { RoomSocketManager } from "../socketManager.mjs";

export class GameQueueCreationPage {
  static render() {
    renderNavBar();

    document.body.innerHTML += `
      <div id="gameQueueCreationSection" class="box">
        <p style="color: #2e8b57; font-size: 16px; text-align: center; margin-bottom: 0px;">Please select the number of members of PageManager Pong Tournament.</p><br/>
        <form id="createQueueForm" class="columnAlignedForm" action="" method="">
          <div>
            <input type="radio" class="choice" name="numOfMembers" value="2" />
            <label class="green">2</label><br />
          </div>
          <div>
            <input type="radio" class="choice" name="numOfMembers" value="4" />
            <label class="green">4</label><br />
          </div>
          <input id="createQueueButton" class="submitInput" type="submit" value="create queue" />
        </form>
      </div>
    `;

    const createQueueForm = document.getElementById("createQueueForm");
    const radioButtons = document.getElementsByName("numOfMembers");

    createQueueButton.disabled = true;

    radioButtons.forEach((rb) => {
      rb.addEventListener("click", () => {
        createQueueButton.disabled = false;
      });
    });

    createQueueForm.addEventListener("submit", (event) => {
      event.preventDefault();

      Array.from(document.getElementsByClassName("choice")).forEach(
        (choice) => {
          if (choice.checked) {
            clearExceptNavBar();
            GameQueuePage.render();
            RoomSocketManager.maxNumOfParticipant = Number(choice.value);
            RoomSocketManager.emitMakeRoom(
              Math.trunc(Math.random() * 10000).toString(),
              Number(choice.value)
            );
          }
        }
      );
    });

    PageManager.currentpageStatus = PageManager.pageStatus.gameQueueCreation;
  }

  static destroy() {
    const gameQueueCreationSection = document.getElementById(
      "gameQueueCreationSection"
    );
    gameQueueCreationSection.innerHTML = "";
    gameQueueCreationSection.parentNode.removeChild(gameQueueCreationSection);
  }
}
