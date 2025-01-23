import { LoginPage, PageManager } from "./modules/page.mjs";

document.addEventListener("DOMContentLoaded", () => {
    window.addEventListener("popstate", PageManager.popStateEvent);
    LoginPage.renderLoginPageWithPushHistory();
});