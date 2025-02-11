import {
  renderCentralBox,
  clearBody,
  removeBodyProperty,
} from "./lowRankElements.mjs";
import { JWT } from "../authentication/jwt.mjs";
import { TwoFA } from "../authentication/twoFA.mjs";
import { logout } from "../authentication/logout.mjs";
import { replaceAllScriptChar } from "../security.mjs";
import { PageManager } from "./manager.mjs";
import { MainPage } from "./main.mjs";

export class TwoFAPage {
  static renderAndReplaceHistroy(url) {
    const centralBox = renderCentralBox();

    console.log(TwoFA.isNewUser);
    if (TwoFA.isNewUser === true) {
      centralBox.innerHTML += `
        <form id="twoFAUserNameForm" action="" method="">
          <input id="otpUserNameInput" type="password" class="form-control" placeholder="please input OTP user name" />
          <input id="otpUserNameSubmit" type="submit" class="btn btn-info mb-3" value="submit" />
        </form>
      `;

      document.getElementById("twoFAUserNameForm").onsubmit = async (event) => {
        event.preventDefault();

        const otpUserName = replaceAllScriptChar(
          document.getElementById("otpUserNameInput").value
        );

        const otpUrl = await TwoFA.sendOTPUserNameToServer(otpUserName);

        const twoFAForm = document.getElementById("twoFAUserNameForm");
        twoFAForm.innerHTML = "";
        twoFAForm.parentNode.removeChild(twoFAForm);

        centralBox.innerHTML += `
          <form id="twoFAOTPCodeForm" action="" method="">
            <input id="otpCodeInput" type="password" class="form-control" placeholder="please input otp code" />
            <input id="otpCodeSubmit" type="submit" class="btn btn-info mb-3" value="submit" />
          </form>
        `;

        document.getElementById("twoFAOTPCodeForm").onsubmit = async (
          event
        ) => {
          event.preventDefault();
          const otpCode = replaceAllScriptChar(
            document.getElementById("otpCodeInput").value
          );

          TwoFAPage.sendOTPCodeWhileResponseOk(otpCode);
        };

        QRCode.toCanvas(otpUrl, { width: 256 }, function (error, canvas) {
          if (error) {
            console.error(error);
          } else {
            centralBox.appendChild(canvas);
          }
        });
      };
    } else {
      centralBox.innerHTML += `
          <p id="otpName"></p>
          <form id="twoFAOTPCodeForm" action="" method="">
            <input id="otpCodeInput" type="text" class="form-control" placeholder="please input otp code" />
            <input id="otpCodeSubmit" type="submit" class="btn btn-info mb-3" value="submit" />
          </form>
        `;

      // document.getElementById(
      //   "otpName"
      // ).textContent = `Your Otp Name: ${TwoFA.getOTPUserNameFromServer().then()}`;
      TwoFA.getOTPUserNameFromServer()
        .then(v => {
          document.getElementById("otpName").textContent = `Your Otp Name : ${v}`
        })

      document.getElementById("twoFAOTPCodeForm").onsubmit = async (event) => {
        event.preventDefault();
        const otpCode = replaceAllScriptChar(
          document.getElementById("otpCodeInput").value
        );

        TwoFAPage.sendOTPCodeWhileResponseOk(otpCode);
      };
    }

    PageManager.currentpageStatus = PageManager.pageStatus.twoFA;
    history.replaceState(PageManager.pageStatus.twoFA, "", url);
  }

  static sendOTPCodeWhileResponseOk = async (otpCode) => {
    let response = await TwoFA.sendOTPCodeToServer(
      JWT.getJWTTokenFromCookie().accessToken,
      otpCode
    );
    if (response.ok) {
      TwoFAPage.destroy();
      MainPage.renderAndPushHistory();
    } else {
      const text = await response.text();
      console.log(`status : ${response.status}, text : ${text}`);
      switch (response.status) {
        case 400:
          alert("wrong code. please input again");
          break;
        case 401:
          if (text === "jwt.invalid") {
            alert("please login again");
            logout();
          } else if (text === "jwt.expired") {
            try {
              await JWT.getNewToken();
              console.log("Throw!!!!!!!!!!!!!!!");
              await TwoFAPage.sendOTPCodeWhileResponseOk(otpCode);
            } catch (e) {
              logout();
            }
            return;
          }
          break;
        default:
          break;
      }
    }
  };

  static destroy() {
    removeBodyProperty();
    clearBody();
  }
}
