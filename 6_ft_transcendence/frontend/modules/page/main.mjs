import { renderNavBar, bindEventToNavBar } from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";

export class MainPage {
  static render() {
    renderNavBar();
    bindEventToNavBar();
    PageManager.currentpageStatus = PageManager.pageStatus.main;
  }

  static renderAndPushHistory() {
    MainPage.render();
    history.pushState(PageManager.pageStatus.main, "");
  }
}
