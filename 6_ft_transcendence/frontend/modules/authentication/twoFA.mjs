import { AUTH_CONTAINER } from "./globalConstants.mjs";
import { JWT } from "./jwt.mjs";
import { safe_fetch } from "../utility.mjs";

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
  