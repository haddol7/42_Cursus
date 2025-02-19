import { AUTH_URL } from "./globalConstants.mjs";
import { JWT } from "./jwt.mjs";
import { logout } from "./logout.mjs";
import { LOGIN_EXPIRED_MSG } from "./globalConstants.mjs";

export class TwoFA {
  static isNewUser = true;

  static sendOTPUserNameToServer = async (otpUserName) => {
    const option = JWT.getOptionWithAccessToken("POST", { name: otpUserName });
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
          alert(`${LOGIN_EXPIRED_MSG}(${e})`);
          logout();
        }
      }
    }
  };

  static getOTPUserNameFromServer = async () => {
    const option = JWT.getOptionWithAccessToken("GET");
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
          alert(`${LOGIN_EXPIRED_MSG}(${e})`);
          logout();
        }
      }
    }
  };

  static sendOTPCodeToServer = async (otpCode) => {
    const option = JWT.getOptionWithAccessToken("POST", { code: otpCode });
    // 테스트를 위해 요청을 일시적으로 변경 /2fa -> /2fa/mock
    const response = await fetch(`${AUTH_URL}2fa`, option);

    if (!response.ok) {
      const text = await response.text();

      if (text === "jwt.expired") {
        try {
          await JWT.getNewToken();
          await JWT.sendOTPCodeToServer(otpCode);
        } catch (e) {
          throw e;
        }
      } else throw new Error(text);
    }
  };
}
