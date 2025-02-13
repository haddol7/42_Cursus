import { renderNavBar, bindEventToNavBar } from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";
import { USER_URL } from "../authentication/globalConstants.mjs";
import { JWT } from "../authentication/jwt.mjs";
import { WHEN_EXPIRED } from "../authentication/globalConstants.mjs";
import { replaceAllScriptChar } from "../security.mjs";

export class EditProfilePage {
  static render() {
    renderNavBar();

    document.body.innerHTML += `
      <div id="editProfileSection" style="border: 1px solid gray; margin: 4px;">
        <div id="currentProfileInfo" class="box" style="display: grid; grid-template-columns: 1fr 1fr;">
          <div>
            <h5 class="centerAlignedTitle">Current Avartar</h5>
            <img id="currentAvartar" src="default.png" class="image" width="200px"/>
          </div>
          <div>
            <div class="blockWrapher">
              <h6 class="leftAlignedTitle">current nickname : </h6>
              <p id="currentNick" class="paragraph"></p>
            </div>
            <div class="blockWrapher">
              <h6 class="leftAlignedTitle">current memo : </h6>
              <p id="currentMemo" class="paragraph"></p>
            </div>
          </div>
        </div>
        <div class="box">
          <form id="editProfileForm" class="columnAlignedForm" action="" method="">
            <input id="newAvartar" class="fileInput" type="file" placeholder="new avartar image" style="width: 70%"/>
            <input id="newNick" class="textInput" type="text" placeholder="new nickname" style="width: 70%"/>
            <input id="newMemo" class="textInput" type="text" placeholder="new memo" style="width: 70%"/>
            <input type="submit" class="submitInput" value="edit"/>
          </form>
        </div>
      </div>
    `;

    bindEventToNavBar();
    EditProfilePage.#showCurrentProfile();
    document
      .getElementById("editProfileForm")
      .addEventListener("submit", EditProfilePage.#submitEditedProfile);

    PageManager.currentpageStatus = PageManager.pageStatus.editProfile;
  }

  static #showCurrentProfile = async () => {
    const response = await fetch(USER_URL, JWT.getOptionWithAccessToken("GET"));

    const json = await response.json();
    if (response.ok) {
      document.getElementById("currentAvartar").src = json.image_url;
      document.getElementById("currentNick").textContent = json.user_name;
      document.getElementById("currentMemo").memo = json.memo;
    } else {
      if (response.status === 401 && json.error === WHEN_EXPIRED) {
        try {
          await JWT.getNewToken();
          await EditProfilePage.#showCurrentProfile();
        } catch (e) {
          alert(e.message);
        }
      } else alert(json.error);
    }
  };

  static #submitEditedProfile = async (event) => {
    event.preventDefault();

    const newAvartar = document.getElementById("newAvartar");
    const newNick = document.getElementById("newNick");
    const newMemo = document.getElementById("newMemo");

    const imgData = new FormData();
    console.log(newAvartar.files[0]);
    imgData.append("image_url", newAvartar.files[0]);
    imgData.append("user_name", replaceAllScriptChar(newNick.value));
    imgData.append("memo", replaceAllScriptChar(newMemo.value));

    const response = await fetch(`${USER_URL}`, {
      method: "PUT",
      headers: {
        Authorization: `Bearer ${JWT.getJWTTokenFromCookie().accessToken}`,
      },
      body: imgData,
    });

    if (!response.ok) {
      const json = await response.json();

      if (response.status === 401 && json.error === WHEN_EXPIRED) {
        await JWT.getNewToken();
        await EditProfilePage.#submitEditedProfile(event);
      } else alert(json.error);
    }
  };

  static renderAndPushHistory() {
    EditProfilePage.render();
    history.pushState(PageManager.pageStatus.editProfile, "");
  }

  static destroy() {
    const editProfileSection = document.getElementById("editProfileSection");
    editProfileSection.innerHTML = "";
    editProfileSection.parentNode.removeChild(editProfileSection);
  }
}
