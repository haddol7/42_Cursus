import { LoginPage } from "./modules/page/login.mjs";
import { PageManager } from "./modules/page/manager.mjs";
import { TwoFAPage } from "./modules/page/twoFA.mjs";
import { FTOauth } from "./modules/authentication/ftOauth.mjs";

document.addEventListener("DOMContentLoaded", async () => {
  window.addEventListener("popstate", PageManager.popStateEvent);

  if (FTOauth.isAlreadyOauth()) {
    try {
      await FTOauth.sendFTOauthCodeToServer();
    } catch (e) {
      console.error(e);
    }

    const url = FTOauth.removeCodeFromUrl();
    TwoFAPage.render(url);
  } else {
    LoginPage.renderAndReplaceHistory();
  }
});
