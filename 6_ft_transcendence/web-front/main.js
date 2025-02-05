import { LoginPage } from "./modules/page/login.mjs";
import { PageManager } from "./modules/page/manager.mjs";
import { TwoFAPage } from "./modules/page/twoFA.mjs";
import { FTOauth } from "./modules/authentication/ftOauth.mjs";

document.addEventListener("DOMContentLoaded", () => {
  window.addEventListener("popstate", PageManager.popStateEvent);
  if (
    history.state === null ||
    history.state.page === PageManager.pageStatus.login.page
  ) {
    if (FTOauth.isAlreadyOauth()) {
      try {
        FTOauth.sendFTOauthCodeToServer();
      } catch (e) {
        console.error(e);
      }

      const url = FTOauth.removeCodeFromUrl();
      TwoFAPage.renderAndReplaceHistroy(url);
    } else {
      LoginPage.renderAndReplaceHistory();
    }
  } else if (history.state.page === PageManager.pageStatus.twoFA.page)
    history.forward();
});
