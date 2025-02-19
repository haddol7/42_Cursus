import { USER_URL, WHEN_EXPIRED,LOGIN_EXPIRED_MSG } from "../authentication/globalConstants.mjs";
import { JWT } from "../authentication/jwt.mjs";
import { logout } from "../authentication/logout.mjs";
import {
  bindEventToNavBar,
  clearExceptNavBar,
  renderNavBar,
} from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";
import { MyPage } from "./my.mjs";

export class FriendPage {
  static lastfriendName = "Dumm";
  static render(friendName) {
    if (friendName === null || friendName === undefined)
      friendName = FriendPage.lastfriendName;
    else FriendPage.lastfriendName = friendName;

    renderNavBar();

    document.body.innerHTML += `
      <div id="friendSection">
        <h6 class="centerAlignedTitle">Friend Info</h6>
        <div id="friendProfileInfo" class="box oneToOneRatioWrapher">
            <div>
                <div>
                    <img id="friendAvartar" class="image" width="200px"/>
                </div>
            </div>
            <div>
                <div class="blockWrapher">
                    <h6 class="leftAlignedTitle">nickname : </h6>
                    <p id="friendNick" class="paragraph"></p>
                </div>
                <div class="blockWrapher">
                    <h6 class="leftAlignedTitle">memo : </h6>
                    <p id="friendMemo" class="paragraph"></p>
                </div>
                <div class="blockWrapher">
                    <h6 class="leftAlignedTitle">win count : </h6>
                    <p id="friendWinCnt" class="paragraph"></p>
                </div>
                <div class="blockWrapher">
                    <h6 class="leftAlignedTitle">lose count : </h6>
                    <p id="friendLoseCnt" class="paragraph"></p>
                </div>
            </div>
        </div>
        <a id="backToPageLink" class="nav justify-content-center link">Back to My Page</a>
      </div>
    `;

    bindEventToNavBar();
    // async 함수지만 반환값을 사용하지 않고
    // 호출 순서의 의존성이 없어서 await으로 호출하지 않습니다.
    FriendPage.#showFriendProfile(friendName);

    document
      .getElementById("backToPageLink")
      .addEventListener("click", (event) => {
        event.preventDefault();
        clearExceptNavBar();
        MyPage.renderAndPushHistory();
      });

    PageManager.currentpageStatus = PageManager.pageStatus.friend;
  }

  static #showFriendProfile = async (friendName) => {
    const response = await fetch(
      `${USER_URL}?user_name=${friendName}`,
      JWT.getOptionWithAccessToken("GET")
    );

    const json = await response.json();
    if (response.ok) {
      document.getElementById("friendAvartar").src = json.image_url;
      document.getElementById("friendNick").textContent = json.user_name;
      document.getElementById("friendMemo").textContent = json.memo;
      document.getElementById("friendWinCnt").textContent = json.win_cnt;
      document.getElementById("friendLoseCnt").textContent = json.lose_cnt;
    } else {
      if (response.status === 401 && json.error === WHEN_EXPIRED) {
        try {
          await JWT.getNewToken();
          await FriendPage.#showFriendProfile(friendName);
        } catch (e) {
          alert(`${LOGIN_EXPIRED_MSG}(${e})`);
          logout();
        }
      } else alert(json.error);
    }
  };

  static renderAndPushHistory(friend) {
    FriendPage.render(friend);
    history.pushState(PageManager.pageStatus.friend, "");
  }

  static destroy() {
    const friendSection = document.getElementById("friendSection");
    friendSection.innerHTML = "";
    friendSection.parentNode.removeChild(friendSection);
  }
}
