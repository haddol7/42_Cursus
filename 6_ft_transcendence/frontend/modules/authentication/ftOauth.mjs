import { AUTH_CONTAINER } from "./globalConstants.mjs";
import { safe_fetch } from "../utility.mjs";
import { JWT } from "./jwt.mjs";

export class FTOauth {
  static isAlreadyOauth() {
    if (
      window.location.href === "http://localhost:5500/42-ascension/web-front/"
    )
      return false;
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
    const response = await safe_fetch(`${AUTH_CONTAINER}auth/42/code` + code);

    if (response === null) throw new Error("Wrong Code");

    const json = await response.json();
    JWT.setNewJWTTokenOnCookie(json.access_token, json.refresh_token);
  };
}
