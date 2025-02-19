import {
  renderNavBar,
  bindEventToNavBar,
  clearExceptNavBar,
} from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";
import { EditProfilePage } from "./editProfile.mjs";
import { JWT } from "../authentication/jwt.mjs";
import { USER_URL, WHEN_EXPIRED } from "../authentication/globalConstants.mjs";
import { replaceAllScriptChar } from "../security.mjs";
import { FriendPage } from "./friend.mjs";
import { logout } from "../authentication/logout.mjs";
import { LOGIN_EXPIRED_MSG } from "../authentication/globalConstants.mjs";

export class MyPage {
  static render() {
    renderNavBar();

    document.body.innerHTML += `
        <div id="mainPageSection" style="display: grid; grid-template-columns: 1fr 1fr;">
          <div id="leftSection">
            <div id="profileSection" class="box">
              <h5 class="centerAlignedTitle">User Profile</h5>
              <img id="myAvartar" class="image" alt="avartar" width="200" />
              <div class="oneToOneRatioWrapher">
                <h6 class="leftAlignedTitle">Nick : </h6>
                <p id="myNick" class="paragraph"></p>
              </div>
              <div class="oneToOneRatioWrapher">
                <h6 class="leftAlignedTitle">Memo : </h6>
                <p id="myMemo" class="paragraph"></p>
              </div>
              <div class="oneToOneRatioWrapher">
                <h6 class="leftAlignedTitle">win count : </h6>
                <p id="winCnt" class="paragraph"></p>
              </div>
              <div class="oneToOneRatioWrapher">
                <h6 class="leftAlignedTitle">lose count : </h6>
                <p id="loseCnt" class="paragraph"></p>
              </div>
            </div>
          </div>
          <div id="rightSection" class="box">
            <form id="addNewFriend" class="rowAlignedForm" action="" method="">
              <input id="newFriendName" class="textInput" type="text" placeholder="Please input friend's name"/>
              <input class="submitInput" type="submit" value="Add Friend"/>
            </form>
            <h5 class="centerAlignedTitle" style="margin-top: 20px;">Friend List</h5>
          </div>
          <a id="editProfileLink" class="nav justify-content-center link">edit profile</a>
        </div>
        `;

    bindEventToNavBar();

    document
      .getElementById("editProfileLink")
      .addEventListener("click", (event) => {
        event.preventDefault();
        clearExceptNavBar();
        EditProfilePage.renderAndPushHistory();
      });

    document
      .getElementById("addNewFriend")
      .addEventListener("submit", (event) => {
        event.preventDefault();
        MyPage.#addFriend(document.getElementById("newFriendName").value);
      });

    MyPage.#requestProfileToServer()
      .then(() => {
        MyPage.#requestFriendListToServer();
      })
      .catch(() => {});

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
    const response = await fetch(USER_URL, JWT.getOptionWithAccessToken("GET"));

    const json = await response.json();

    if (response.ok) {
      MyPage.#updateProfile(
        json.image_url,
        json.user_name,
        json.memo,
        json.win_cnt,
        json.lose_cnt
      );
    } else {
      if (response.status === 401 && json.error === WHEN_EXPIRED) {
        try {
          await JWT.getNewToken();
          await MyPage.#requestProfileToServer();
        } catch (e) {
          alert(`${LOGIN_EXPIRED_MSG}(${e})`);
          logout();
          throw new Error(json.error);
        }
      } else {
        alert(json.error);
        throw new Error(json.error);
      }
    }
  };

  static #updateProfile(image_url, user_name, memo, win_cnt, lose_cnt) {
    document.getElementById("myAvartar").src = image_url;
    document.getElementById("myNick").textContent = user_name;
    document.getElementById("myMemo").textContent = memo;
    document.getElementById("winCnt").textContent = win_cnt;
    document.getElementById("loseCnt").textContent = lose_cnt;
  }

  static #requestFriendListToServer = async () => {
    const response = await fetch(
      `${USER_URL}friend`,
      JWT.getOptionWithAccessToken("GET")
    );

    const json = await response.json();

    if (response.ok) {
      MyPage.#updateFriendList(json);
    } else {
      if (response.status === 401 && json.error === WHEN_EXPIRED) {
        try {
          await JWT.getNewToken();
          await MyPage.#requestFriendListToServer();
        } catch (e) {
          alert(`${LOGIN_EXPIRED_MSG}(${e})`);
          logout();
        }
      } else alert(json.error);
    }
  };

  static #updateFriendList(fl) {
    let friendList = document.getElementById("friendList");

    if (fl.length === 0) {
      if (friendList !== null) {
        friendList.innerHTML = "";
        friendList.parentNode.removeChild(friendList);
      }
      return;
    }

    if (friendList !== null) friendList.innerHTML = "";
    else {
      friendList = document.createElement("div");
      friendList.id = "friendList";
      friendList.classList.add("box");
      document.getElementById("rightSection").appendChild(friendList);
    }

    fl.forEach((value) => {
      const friendInfo = document.createElement("div");
      friendInfo.classList.add("oneToOneRatioWrapher");
      friendList.appendChild(friendInfo);

      const friendLink = document.createElement("a");
      friendLink.classList.add("link");
      friendLink.textContent = String(value.user_name);
      friendInfo.appendChild(friendLink);

      const friendOnlineStatus = document.createElement("p");
      friendOnlineStatus.classList.add("paragraph");
      if (value.online_status) friendOnlineStatus.textContent = "online";
      else friendOnlineStatus.textContent = "offline";
      friendInfo.appendChild(friendOnlineStatus);

      friendLink.addEventListener("click", (event) => {
        event.preventDefault();
        clearExceptNavBar();
        FriendPage.renderAndPushHistory(value.user_name);
      });
    });
  }

  static #addFriend = async (name) => {
    const response = await fetch(
      `${USER_URL}friend`,
      JWT.getOptionWithAccessToken("POST", {
        user_name: replaceAllScriptChar(name),
      })
    );

    const json = await response.json();

    if (response.ok) {
      await MyPage.#requestFriendListToServer();
    } else {
      if (response.status === 401 && json.error === WHEN_EXPIRED) {
        try {
          await JWT.getNewToken();
          await MyPage.#addFriend(name);
        } catch (e) {
          alert(`${LOGIN_EXPIRED_MSG}(${e})`);
          logout();
        }
      } else alert(json.error);
    }
  };
}
