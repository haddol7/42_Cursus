import { AUTH_URL } from "./globalConstants.mjs";
import { JWT } from "./jwt.mjs";
// import { safe_fetch } from "../utility.mjs";

export class TwoFA {
  static isNewUser = true;

  static sendOTPUserNameToServer = async (otpUserName) => {
    const option = JWT.getOptionWithToken(
      JWT.getJWTTokenFromCookie().accessToken,
      "POST",
      JSON.stringify({ name: otpUserName })
    );
    const response = await fetch(`${AUTH_URL}2fa/new`, option);

    if (response.ok === true) {
      const json = await response.json();
      return json.url;
    } else {
      const text = await response.text();
      if (response.status === 401 && text === "jwt.expired") {
        try {
          await JWT.getNewToken();
          return TwoFA.sendOTPUserNameToServer(otpUserName);
        } catch (e) {
          alert(e);
        }
      }
    }
  };

  static getOTPUserNameFromServer = async () => {
    const option = JWT.getOptionWithToken(
      JWT.getJWTTokenFromCookie().accessToken,
      "GET"
    );
    const response = await fetch(`${AUTH_URL}2fa`, option);

    if (response.ok === true) {
      const json = await response.json();
      return json.name;
    } else {
      const text = (await response).text();
      if (response.status === 401 && text === "jwt.expired") {
        try {
          await JWT.getNewToken();
          return TwoFA.getOTPUserNameFromServer();
        } catch (e) {
          alert(e);
        }
      }
    }
  };

  static sendOTPCodeToServer = async (token, otpCode) => {
    const option = JWT.getOptionWithToken(
      token,
      "POST",
      JSON.stringify({ code: otpCode })
    );
    // 테스트를 위해 요청을 일시적으로 변경 /2fa -> /2fa/mock
    const response = await fetch(`${AUTH_URL}2fa`, option);
    return response;
  };
}
