import { clearBody, removeBodyProperty } from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";

export class ErrorPage {
  static render(errorText) {
    clearBody();
    removeBodyProperty();

    document.body.innerHTML = `${errorText}`;

    PageManager.currentpageStatus = PageManager.pageStatus.error;
  }
}
