import { LoginPage } from "./modules/page/login.mjs";
import { PageManager } from "./modules/page/manager.mjs";
import { TwoFAPage } from "./modules/page/twoFA.mjs";
import { FTOauth } from "./modules/authentication/ftOauth.mjs";

document.addEventListener("DOMContentLoaded", () => {
  window.addEventListener("popstate", PageManager.popStateEvent);
  console.log(FTOauth.isAlreadyOauth());
  if (
    history.state === null ||
    history.state.page === PageManager.pageStatus.login.page
  ) {
    console.log("1");
    if (FTOauth.isAlreadyOauth()) {
      console.log("2");
      try {
        FTOauth.sendFTOauthCodeToServer();
      } catch (e) {
        console.error(e);
      }

      const url = FTOauth.removeCodeFromUrl();
      TwoFAPage.renderAndReplaceHistroy(url);
    } else {
      console.log("3");
      LoginPage.renderAndReplaceHistory();
    }
  } else if (history.state.page === PageManager.pageStatus.twoFA.page)
    console.log("4");
    history.forward();
});
