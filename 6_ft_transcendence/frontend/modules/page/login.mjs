import {
  renderCentralBox,
  removeBodyProperty,
  clearBody,
} from "./lowRankElements.mjs";
import { JWT } from "../authentication/jwt.mjs";
import { logout } from "../authentication/logout.mjs";
import { MainPage } from "./main.mjs";
import { PageManager } from "./manager.mjs";
import { CLIENT_ID } from "../authentication/globalConstants.mjs";

export class LoginPage {
  // 로그인 페이지를 화면에 렌더링한다.
  static render() {
    const centralBox = renderCentralBox();

    if (JWT.getJWTTokenFromCookie() === null) {
      const linkTo42Oauth = document.createElement("a");

      linkTo42Oauth.classList.add("submitInput");
      linkTo42Oauth.textContent = "42Oauth";

      centralBox.appendChild(linkTo42Oauth);

      linkTo42Oauth.onclick = (event) => {
        event.preventDefault();
        window.location.href =
          "https://api.intra.42.fr/oauth/authorize" +
          `?client_id=${CLIENT_ID}` +
          `&redirect_uri=${window.location.href}` +
          "&response_type=code";
      };
    } else {
      const linkToMainPage = document.createElement("a");

      linkToMainPage.classList.add("submitInput");
      linkToMainPage.textContent = "return to main page";
      centralBox.appendChild(linkToMainPage);

      linkToMainPage.onclick = (event) => {
        event.preventDefault();
        LoginPage.destroy();
        MainPage.renderAndPushHistory();
      };
      const logoutButton = document.createElement("a");

      logoutButton.classList.add("submitInput");
      logoutButton.textContent = "logout";
      centralBox.appendChild(logoutButton);

      logoutButton.onclick = (event) => {
        event.preventDefault();
        logout();
      };
    }

    PageManager.currentpageStatus = PageManager.pageStatus.login;
  }

  // 히스토리를 갱신하며 로그인 페이지를 화면에 렌더링한다.
  static renderAndPushHistory() {
    LoginPage.render();
    history.pushState(PageManager.pageStatus.login, "");
  }

  static renderAndReplaceHistory() {
    LoginPage.render();
    history.replaceState(PageManager.pageStatus.login, "");
  }

  // 로그인 페이지를 화면에서 지운다.
  static destroy() {
    removeBodyProperty();
    clearBody();
  }
}
