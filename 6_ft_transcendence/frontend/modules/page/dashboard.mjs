import { renderNavBar, bindEventToNavBar } from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";

export class DashBoardPage {
  static render() {
    renderNavBar();

    document.body.innerHTML += `
      <div id="dashBoardSection" style="border: 1px solid gray; margin: 4px;">dash board section</div>
    `;

    bindEventToNavBar();
    PageManager.currentpageStatus = PageManager.pageStatus.dashBoard;
  }

  static renderAndPushHistory() {
    DashBoardPage.render();
    history.pushState(PageManager.pageStatus.dashBoard, "");
  }

  static destroy() {
    const dashBoardSection = document.getElementById("dashBoardSection");
    dashBoardSection.innerHTML = "";
    dashBoardSection.parentNode.removeChild(dashBoardSection);
  }
}
