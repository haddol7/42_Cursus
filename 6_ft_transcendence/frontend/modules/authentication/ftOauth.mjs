import { AUTH_URL } from "./globalConstants.mjs";
import { safe_fetch } from "../utility.mjs";
import { JWT } from "./jwt.mjs";
import { TwoFA } from "./twoFA.mjs";

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
    // 테스트를 위해 일시적으로 code query 문을 변경
    // const code = `?code=temp&user_name=${Math.trunc(Math.random() * 10000).toString()}`;
    // 테스트를 위해 일시적으로 요청을 변경 42/code -> 42/code/mock
    const response = await safe_fetch(`${AUTH_URL}42/code` + code);

    if (response === null) throw new Error("Wrong Code");

    const json = await response.json();
    alert(json);
    await JWT.setNewJWTTokenOnCookie(json.accessToken, json.refreshToken);
    TwoFA.isNewUser = json.isnew;
    console.log(`isNewUser : ${TwoFA.isNewUser}, isnew : ${json.isnew}`);
  };
}
