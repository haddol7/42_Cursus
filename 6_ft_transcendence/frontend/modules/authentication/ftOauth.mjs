import { AUTH_CONTAINER } from "./globalConstants.mjs";
import { safe_fetch } from "../utility.mjs";
import { JWT } from "./jwt.mjs";

export class FTOauth {
  static isAlreadyOauth() {
    if (window.location.href === "https://localhost/") return false;
    return true;
  }

  static getFtOauthCodeFromUrl() {
    const codePos = window.location.href.indexOf("?code=");
    const code = window.location.href.substring(codePos);
    return code;
  }

  static removeCodeFromUrl() {
    const url = new URL(window.location);
    url.searchParams.delete("code");
    return url.href;
  }

  static sendFTOauthCodeToServer = async () => {
    const code = FTOauth.getFtOauthCodeFromUrl();
    const response = await safe_fetch(`${AUTH_CONTAINER}42/code` + code);

    if (response === null) throw new Error("Wrong Code");

    const json = await response.json();
    alert(json);
    JWT.setNewJWTTokenOnCookie(json.accessToken, json.refreshToken);
  };
}
