import { clearBody, removeBodyProperty } from "../page/lowRankElements.mjs";
import { JWT } from "./jwt.mjs";
import { AUTH_URL } from "./globalConstants.mjs";
import { LoginPage } from "../page/login.mjs";

// logout()은 jwt 토큰을 전부 지우고 로그인 페이지를 새로 로드한다.
// 그러므로 logout()을 호출했다면 그 이후에 어떠한 처리도(DOM, 이벤트 관련 처리 등등) 없어야 한다.
export const logout = async () => {
  const response = await fetch(
    `${AUTH_URL}logout`,
    JWT.getOptionWithToken(JWT.getJWTTokenFromCookie().accessToken, "DELETE")
  );

  if (!response.ok) {
    const text = await response.text();
    if (text === "jwt.expired") {
      try {
        await JWT.getNewToken();
        logout();
      } catch (e) {
        alert(e);
      } finally {
        return;
      }
    }
  }

  JWT.clearCookie();
  clearBody();
  removeBodyProperty();
  LoginPage.renderAndReplaceHistory();
};
