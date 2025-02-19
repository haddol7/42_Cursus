import { AUTH_URL, SERVER_ADDRESS } from "./globalConstants.mjs";
import { JWT } from "./jwt.mjs";
import { TwoFA } from "./twoFA.mjs";

export class FTOauth {
  static isAlreadyOauth() {
    if (window.location.href === SERVER_ADDRESS) return false;
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
    const response = await fetch(`${AUTH_URL}42/code` + code);

    const json = await response.json();

    if (response.ok) {
      JWT.setNewJWTTokenOnCookie(json.accessToken, json.refreshToken);
      TwoFA.isNewUser = json.isnew;
    } else throw new Error(await response.text());
  };
}
