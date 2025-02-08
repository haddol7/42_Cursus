import {
  renderNavBar,
  bindEventToNavBar,
  clearBody,
} from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";
import { EditProfilePage } from "./editProfile.mjs";
import { JWT } from "../authentication/jwt.mjs";
import { USER_URL } from "../authentication/globalConstants.mjs";

export class MyPage {
  static render() {
    renderNavBar();

    document.body.innerHTML += `
        <div id="mainPageSection" style="display: grid; grid-template-columns: 1fr 1fr;">
          <div id="leftSection">
            <div id="profileSection" style="display: grid; grid-template-columns: 1fr 2fr; border: 1px solid gray; margin: 4px;">
              <div style="margin: 4px;">
                <a id="editProfileLink" style="margin-left: 60px; text-decoration: none;">edit profile</a>
                <img id="myAvartar" alt="avartar" width="200" />
              </div>
              <div style="border: 1px solid gray; margin: 4px;">
                <p id="myNick" style="border: 1px solid gray; margin: 16px;"></p>
                <p id="myMemo" style="border: 1px solid gray; margin: 16px;"></p>
              </div>
            </div>
          </div>
          <div id="rightSection">
            <form id="addNewFriend" action="" method="" style="display: grid; grid-template-columns: 4fr 1fr; border: 1px solid gray; margin: 4px;">
              <input id="newFriendName" type="text" class="form-control" placeholder="user search bar" style="margin: 16px;" />
              <input type="submit" class="btn btn-info mb-3" value="search" style="margin: 16px;" />
            </form>
            <div id="friendList" style="border: 1px solid gray; margin: 4px;"></div>
          </div>
        </div>`;

    bindEventToNavBar();

    document
      .getElementById("editProfileLink")
      .addEventListener("click", (event) => {
        event.preventDefault();
        clearBody();
        EditProfilePage.renderAndPushHistory();
      });

    document
      .getElementById("addNewFriend")
      .addEventListener("submit", (event) => {
        event.preventDefault();
        MyPage.#addFriend(document.getElementById("newFriendName").value);
      });

    MyPage.#requestProfileToServer();
    MyPage.#requestFriendListToServer();

    PageManager.currentpageStatus = PageManager.pageStatus.my;
  }

  static renderAndPushHistory() {
    MyPage.render();
    history.pushState(PageManager.pageStatus.my, "");
  }

  static destroy() {
    const myPageSection = document.getElementById("mainPageSection");
    myPageSection.innerHTML = "";
    myPageSection.parentNode.removeChild(myPageSection);
  }

  static #requestProfileToServer = async () => {
    const response = await fetch(
      `${USER_URL}`,
      JWT.getOptionWithToken(JWT.getJWTTokenFromCookie().accessToken, "GET")
    );

    const json = await response.json();

    if (response.ok) {
      MyPage.#updateProfile();
    } else {
      alert(json.error);
    }
  };

  static #updateProfile(image_url, user_name, memo) {
    const myAvartar = document.getElementById("myAvartar");
    const myNick = document.getElementById("myNick");
    const myMemo = document.getElementById("myMemo");

    myAvartar.src = image_url;
    myNick.textContent = user_name;
    myMemo.textContent = memo;
  }

  static #requestFriendListToServer = async () => {
    const response = await fetch(
      `${USER_URL}friend`,
      JWT.getOptionWithToken(JWT.getJWTTokenFromCookie().accessToken, "GET")
    );

    const json = await response.json();

    if (response.ok) {
      MyPage.#updateFriendList(json);
    } else {
      alert(json.error);
    }
  };

  static #updateFriendList(fl) {
    const friendList = document.getElementById("friendList");
    friendList.innerHTML = "";

    fl.forEach((value) => {
      const friendInfo = document.createElement("p");
      friendList.appendChild(friendInfo);

      const friendLink = document.createElement("a");
      friendInfo.appendChild(friendLink);

      friendLink.textContent = String(value.user_name);
      friendLink.addEventListener("click", async (event) => {
        event.preventDefault();

        // 나중에 아예 새로운 friend page로 넘어가도록 변경
        const response = await fetch(
          `${USER_URL}?user_name=${value.user_name}`,
          JWT.getOptionWithToken(JWT.getJWTTokenFromCookie().accessToken, "GET")
        );
        const json = await response.json();

        if (response.ok) {
          MyPage.#updateProfile(json.image_url, json.user_name, json.memo);
        } else {
          alert(json.error);
        }
      });
    });
  }

  static #addFriend = async (name) => {
    const response = await fetch(
      `${USER_URL}friend`,
      JWT.getOptionWithToken(
        JWT.getJWTTokenFromCookie().accessToken,
        "POST",
        JSON.stringify({
          user_name: name,
        })
      )
    );

    const json = await response.json();

    if (response.ok) {
      MyPage.#requestFriendListToServer();
    } else {
      alert(json.error);
    }
  };
}
