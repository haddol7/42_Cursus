import { safe_fetch } from "./utility.mjs";
import { clearBody, removeBodyProperty, LoginPage, PageManager } from "./page.mjs";

export const CLIENT_ID =
  "u-s4t2ud-402050bcc80fd44b22dd906bb1bf62221445ecf3d54505cccac61564a53428a2";

const AUTH_CONTAINER = "http://localhost:8200/";
const ACCESS_TOKEN_STRING = "accessToken=";
const REFRESH_TOKEN_STRING = "refreshToken=";

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

export class JWT {
  static getJWTTokenFromCookie() {
    const tokens = {};
    document.cookie.split(";").forEach((value) => {
      let property = value.trim();
      if (property.startsWith(ACCESS_TOKEN_STRING))
        tokens.accessToken = property.substring(ACCESS_TOKEN_STRING.length);
      if (property.startsWith(REFRESH_TOKEN_STRING))
        tokens.refreshToken = property.substring(REFRESH_TOKEN_STRING.length);
    });

    if (tokens?.accessToken === undefined || tokens?.refreshToken === undefined)
      return null;

    return tokens;
  }

  static setNewJWTTokenOnCookie(access_token, refresh_token) {
    document.cookie = `${ACCESS_TOKEN_STRING}${access_token};`;
    document.cookie = `${REFRESH_TOKEN_STRING}${refresh_token};`;
  }

  static clearCookie() {
    document.cookie =
      ACCESS_TOKEN_STRING + "; expires=Thu, 01 Jan 1970 00:00:01 GMT;";
    document.cookie =
      REFRESH_TOKEN_STRING + "; expires=Thu, 01 Jan 1970 00:00:01 GMT;";
  }

  static getOptionWithToken(token, _method, _body) {
    const option = {
      method: _method,
      headers: {
        "content-type": "application/json",
        Authorization: `Bearer ${token}`,
      },
    };
    if (_body !== undefined) option.body = _body;

    return option;
  }

  static getNewToken = async () => {
    const option = JWT.getOptionWithToken(
      getJWTTokenFromCookie().refreshToken,
      "POST"
    );
    const response = await fetch(`${AUTH_CONTAINER}auth/refresh`, option);

    if (response.ok) {
      const json = await response.json();
      JWT.setNewJWTTokenOnCookie(json.access_token, json.refresh_token);
    } else {
      if (response.status === 400) throw new Error("refresh token expired");
      else if (response.status === 500)
        throw new Error("server internal error");
    }
  };
}

export class TwoFA {
  static sendOTPUserNameToServer = async (token, otpUserName) => {
    const option = JWT.getOptionWithToken(token, "GET");
    const response = await safe_fetch(
      `${AUTH_CONTAINER}auth/2fa?name=${otpUserName}`,
      option
    );
    const json = await response.json();
    return json.url;
  };

  static sendOTPCodeToServer = async (token, otpCode) => {
    const option = JWT.getOptionWithToken(
      token,
      "POST",
      JSON.stringify({ code: otpCode })
    );
    const response = await fetch(`${AUTH_CONTAINER}auth/2fa`, option);
    return response;
  };
}

// logout()은 jwt 토큰을 전부 지우고 로그인 페이지를 새로 로드한다.
// 그러므로 logout()을 호출했다면 그 이후에 어떠한 처리도(DOM, 이벤트 관련 처리 등등) 없어야 한다.
export const logout = async () => {
  const response = await fetch(
    `${AUTH_CONTAINER}auth/logout`,
    JWT.getOptionWithToken(JWT.getJWTTokenFromCookie().accessToken, "DELETE")
  );

  if (!response.ok) {
    const text = await response.text();
    if (text === "jwt.expired") {
      try {
        JWT.getNewToken();
        logout();
        return;
      } catch (e) {
        alert(e);
      }
    }
  }

  JWT.clearCookie();
  clearBody();
  removeBodyProperty();
  LoginPage.renderLoginPageWithReplaceHistory();
};
