import { clearBody, removeBodyProperty } from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";

export class ErrorPage {
  static render(errorCode) {
    clearBody();
    removeBodyProperty();

    document.body.innerHTML = `${errorCode}`;

    PageManager.currentpageStatus = PageManager.pageStatus.error;
    history.pushState(PageManager.pageStatus.error, "");
  }
}
