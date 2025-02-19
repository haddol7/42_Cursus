import { LoginPage } from "./modules/page/login.mjs";
import { PageManager } from "./modules/page/manager.mjs";
import { TwoFAPage } from "./modules/page/twoFA.mjs";
import { FTOauth } from "./modules/authentication/ftOauth.mjs";
import { JWT } from "./modules/authentication/jwt.mjs";
import { ErrorPage } from "./modules/page/error.mjs";
import { RoomSocketManager } from "./modules/socketManager.mjs";
import { gameSocketDisconnect } from "./game/client.js";

document.addEventListener("DOMContentLoaded", async () => {
  window.addEventListener("popstate", PageManager.popStateEvent);
  window.addEventListener("unload", function () {
    gameSocketDisconnect();
    RoomSocketManager.disconnect();
    JWT.clearCookie();
  });

  if (FTOauth.isAlreadyOauth()) {
    try {
      await FTOauth.sendFTOauthCodeToServer();
      const url = FTOauth.removeCodeFromUrl();
      TwoFAPage.render(url);
    } catch (e) {
      ErrorPage.render(e);
    }
  } else {
    LoginPage.renderAndReplaceHistory();
  }
});
