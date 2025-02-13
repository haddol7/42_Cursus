import { LoginPage } from "./modules/page/login.mjs";
import { PageManager } from "./modules/page/manager.mjs";
import { TwoFAPage } from "./modules/page/twoFA.mjs";
import { FTOauth } from "./modules/authentication/ftOauth.mjs";
import { JWT } from "./modules/authentication/jwt.mjs";

document.addEventListener("DOMContentLoaded", async () => {
  window.addEventListener("popstate", PageManager.popStateEvent);
  window.addEventListener("unload", function () {
    JWT.clearCookie();
  });

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
