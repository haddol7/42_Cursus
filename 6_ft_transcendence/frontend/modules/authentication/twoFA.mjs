import { AUTH_URL } from "./globalConstants.mjs";
import { JWT } from "./jwt.mjs";
import { safe_fetch } from "../utility.mjs";

export class TwoFA {
    static sendOTPUserNameToServer = async (token, otpUserName) => {
      const option = JWT.getOptionWithToken(token, "POST", JSON.stringify({name:otpUserName}));
      const response = await safe_fetch(
        `${AUTH_URL}2fa/new`,
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
      // 테스트를 위해 요청을 일시적으로 변경 /2fa -> /2fa/mock
      const response = await fetch(`${AUTH_URL}2fa/mock`, option);
      return response;
    };
  }
  