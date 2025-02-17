import {
  renderCentralBox,
  clearBody,
  removeBodyProperty,
} from "./lowRankElements.mjs";
import { TwoFA } from "../authentication/twoFA.mjs";
import { replaceAllScriptChar } from "../security.mjs";
import { PageManager } from "./manager.mjs";
import { MainPage } from "./main.mjs";

export class TwoFAPage {
  // static renderAndReplaceHistroy(url) {
  static render(url) {
    const centralBox = renderCentralBox();

    console.log(TwoFA.isNewUser);
    if (TwoFA.isNewUser === true) {
      centralBox.innerHTML += `
        <form id="twoFAUserNameForm" class="smallRowAlignedForm" action="" method="">
          <input id="otpUserNameInput" class="textInput" type="text" placeholder="otp name" />
          <input id="otpUserNameSubmit" class="smallSubmitInput" type="submit" value="submit" />
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
          <form id="twoFAOTPCodeForm" class="smallRowAlignedForm" action="" method="">
            <input id="otpCodeInput" class="textInput" type="text" placeholder="please input otp code" />
            <input id="otpCodeSubmit" class="smallSubmitInput" type="submit" value="submit" />
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
          <form id="twoFAOTPCodeForm" class="smallRowAlignedForm" action="" method="">
            <input id="otpCodeInput" class="textInput" type="text" placeholder="otp code" />
            <input id="otpCodeSubmit" class="smallSubmitInput" type="submit" value="submit" />
          </form>
        `;

      TwoFA.getOTPUserNameFromServer().then((v) => {
        document.getElementById("otpName").textContent = `Your Otp Name : ${v}`;
      });

      document.getElementById("twoFAOTPCodeForm").onsubmit = async (event) => {
        event.preventDefault();
        const otpCode = replaceAllScriptChar(
          document.getElementById("otpCodeInput").value
        );

        TwoFAPage.sendOTPCodeWhileResponseOk(otpCode);
      };
    }

    // PageManager.currentpageStatus = PageManager.pageStatus.twoFA;
    history.replaceState(PageManager.pageStatus.login, "", url);
  }

  static sendOTPCodeWhileResponseOk = async (otpCode) => {
    try {
      await TwoFA.sendOTPCodeToServer(otpCode);
      TwoFAPage.destroy();
      MainPage.renderAndPushHistory();
    } catch (e) {
      if (e.message === "bad_request:code") {
        document.getElementById("otpCodeInput").value = "";
        alert("wrong code. please input again");
      }
      else
        alert(e);
    }
  };

  static destroy() {
    removeBodyProperty();
    clearBody();
  }
}
