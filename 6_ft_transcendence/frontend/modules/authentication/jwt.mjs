import { AUTH_URL } from "./globalConstants.mjs";

export const ACCESS_TOKEN_STRING = "accessToken=";
export const REFRESH_TOKEN_STRING = "refreshToken=";

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
    const refresh_token = JWT.getJWTTokenFromCookie().refreshToken;
    const response = await fetch(`${AUTH_URL}refresh`, {
      method: "POST",
      headers: { "content-Type": "application/json" },
      body: JSON.stringify({ refreshToken: refresh_token }),
    });

    if (response.ok) {
      const json = await response.json();
      JWT.setNewJWTTokenOnCookie(json.access_token, json.refresh_token);
    } else {
      const text = response.text();
      throw new Error(text);
    }
  };
}
