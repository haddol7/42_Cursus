import { renderNavBar, bindEventToNavBar } from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";
import { USER_URL } from "../authentication/globalConstants.mjs";
import { JWT } from "../authentication/jwt.mjs";

export class EditProfilePage {
  static render() {
    renderNavBar();

    document.body.innerHTML += `
      <div id="editProfileSection" style="border: 1px solid gray; margin: 4px;">
        <div id="currentProfileInfo" style="display: grid; grid-template-columns: 1fr 1fr; border: 1px solid gray; margin: 4px;">
          <div>
            <p>current image : </p>
            <img src="sampleAvartar.avif" width="200px" />
          </div>
          <div>
            <p>current nickname : </p>
            <p>current memo : </p>
          </div>
        </div>
        <form id="editProfileForm" action="" method="" id="editAvartarSection" style="border: 1px solid gray; margin: 4px;">
          <input id="newAvartar" type="file" class="form-control" placeholder="new avartar image" style="margin: 16px;" />
          <input id="newNick" type="text" class="form-control" placeholder="new nickname" style="margin: 16px;" />
          <input id="newMemo" type="text" class="form-control" placeholder="new memo" style="margin: 16px;" />
          <input type="submit" class="btn btn-info mb-3" value="edit" style="margin: 16px;" />
        </form>
      </div>
    `;

    bindEventToNavBar();

    document
      .getElementById("editProfileForm")
      .addEventListener("submit", async (event) => {
        event.preventDefault();

        const newAvartar = document.getElementById("newAvartar");
        const newNick = document.getElementById("newNick");
        const newMemo = document.getElementById("newMemo");

        const imgData = new FormData();
        imgData.append("image_url", newAvartar.files[0]);
        imgData.append("user_name", newNick.value);
        imgData.append("memo", newMemo.value);

        const response = await fetch(`${USER_URL}`, {
          method: "PUT",
          headers: {
            Authorization: `Bearer ${JWT.getJWTTokenFromCookie().accessToken}`,
          },
          body: imgData,
        });

        if (!response.ok) {
          const json = await response.json();

          alert(json.error);
        }
      });

    PageManager.currentpageStatus = PageManager.pageStatus.editProfile;
  }

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
