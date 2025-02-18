import { renderNavBar, bindEventToNavBar } from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";
import { activateScrollBar } from "./utility.mjs";

export class MainPage {
  static render() {
    renderNavBar();
    bindEventToNavBar();
    activateScrollBar();
    PageManager.currentpageStatus = PageManager.pageStatus.main;
  }

  static renderAndPushHistory() {
    MainPage.render();
    history.pushState(PageManager.pageStatus.main, "");
  }
}
