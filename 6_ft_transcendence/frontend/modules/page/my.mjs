import {
  renderNavBar,
  bindEventToNavBar,
  clearBody,
} from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";
import { EditProfilePage } from "./editProfile.mjs";
import { JWT } from "../authentication/jwt.mjs";
import { USER_URL, WHEN_EXPIRED } from "../authentication/globalConstants.mjs";

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
              <input id="newFriendName" class="textInput" type="text" placeholder="search user"/>
              <input class="submitInput" type="submit" value="search"/>
            </form>
          </div>
        </div>
        <a id="editProfileLink" class="nav justify-content-center link">edit profile</a>`;

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

    MyPage.#requestProfileToServer().then(() => {
      MyPage.#requestFriendListToServer();
    });

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
      USER_URL,
      JWT.getOptionWithToken(JWT.getJWTTokenFromCookie().accessToken, "GET")
    );

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
          alert(e);
        }
      } else alert(json.error);
    }
  };

  static #updateProfile(image_url, user_name, memo, win_cnt, lose_cnt) {
    const myAvartar = document.getElementById("myAvartar");
    const myNick = document.getElementById("myNick");
    const myMemo = document.getElementById("myMemo");
    const winCnt = document.getElementById("winCnt");
    const loseCnt = document.getElementById("loseCnt");

    // FIXME: 백엔드의 오류가 수정되면 아래의 주석을 해제해야 함
    // myAvartar.src = image_url;
    myNick.textContent = user_name;
    myMemo.textContent = memo;
    winCnt.textContent = win_cnt;
    loseCnt.textContent = lose_cnt;
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
      if (response.status === 401 && json.error === WHEN_EXPIRED) {
        try {
          await JWT.getNewToken();
          await MyPage.#requestFriendListToServer();
        } catch (e) {
          alert(e);
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
      const friendInfo = document.createElement("p");
      friendList.appendChild(friendInfo);

      const friendLink = document.createElement("a");
      friendInfo.appendChild(friendLink);

      friendLink.textContent = String(value.user_name);

      friendLink.addEventListener("click", MyPage.#bindEventToFriendList);
    });
  }

  static #bindEventToFriendList = async (event) => {
    event.preventDefault();
    // 나중에 아예 새로운 friend page로 넘어가도록 변경
    const response = await fetch(
      `${USER_URL}?user_name=${value.user_name}`,
      JWT.getOptionWithToken(JWT.getJWTTokenFromCookie().accessToken, "GET")
    );
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
          await MyPage.#bindEventToFriendList(event);
        } catch (e) {
          alert(e);
        }
      } else alert(json.error);
    }
  };

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
      await MyPage.#requestFriendListToServer();
    } else {
      if (response.status === 401 && json.error === WHEN_EXPIRED) {
        try {
          await JWT.getNewToken();
          await MyPage.#addFriend(name);
        } catch (e) {
          alert(e);
        }
      } else alert(json.error);
    }
  };
}
