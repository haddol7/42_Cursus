import { LoginPage, PageManager, TwoFAPage } from "./modules/page.mjs";
import { FTOauth } from "./modules/authentication.mjs";

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
      TwoFAPage.renderTwoFAPageWithReplaceHistroy(url);
    } else {
      LoginPage.renderLoginPageWithReplaceHistory();
    }
  } else if (history.state.page === PageManager.pageStatus.twoFA.page)
    history.forward();
});
