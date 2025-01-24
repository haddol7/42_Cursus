import { LoginPage, PageManager, TwoFAPage } from "./modules/page.mjs";
import { FTOauth } from "./modules/authentication.mjs";

document.addEventListener("DOMContentLoaded", () => {
    if (FTOauth.isAlreadyOauth())
    {
        console.log(FTOauth.getFtOauthCodeFromUrl());
        TwoFAPage.renderTwoFAPage();
    }

    else
    {
        window.addEventListener("popstate", PageManager.popStateEvent);
        LoginPage.renderLoginPageWithPushHistory();
    }
});