import { renderNavBar } from "./lowRankElements.mjs";
import { GameQueuePage } from "./gameQueue.mjs";
import { PageManager } from "./manager.mjs";
import { SocketManager } from "../socketManager.mjs";
import { clearBody } from "./lowRankElements.mjs";

export class GameQueueCreationPage {
  static render() {
    renderNavBar();

    document.body.innerHTML += `
      <div id="gameQueueCreationSection" style="border: 1px solid gray; margin: 4px;">
        <p style="margin: 4px;">Please select the number of members of PageManager Pong Tournament.</p>
        <form id="createQueueForm" action="" method="">
          <label style="margin: 4px;">  
            <input class="choice" type="radio" name="numOfMembers" value="2" /> 2
          </label><br />
          <label style="margin: 4px;">  
            <input class="choice" type="radio" name="numOfMembers" value="4" /> 4
          </label><br />
          <label style="margin: 4px;">  
            <input class="choice" type="radio" name="numOfMembers" value="8" /> 8
          </label><br />
          <label style="margin: 4px;">  
            <input class="choice" type="radio" name="numOfMembers" value="16" /> 16
          </label><br />
          <label style="margin: 4px;">
            <input id="createQueueButton" type="submit" class="btn btn-info mb-3" value="create queue" />
          </label>
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
            SocketManager.emitMakeRoom("test name", Number(choice.value));
            SocketManager.maxNumOfParticipant = choice.value;
          }
        }
      );

      clearBody();
      GameQueuePage.render();
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
