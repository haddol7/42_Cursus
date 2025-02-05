import {
  renderNavBar,
  bindEventToNavBar,
  clearBody,
} from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";
import { EditProfilePage } from "./editProfile.mjs";

export class MyPage {
  static render() {
    renderNavBar();

    document.body.innerHTML += `
        <div id="mainPageSection" style="display: grid; grid-template-columns: 1fr 1fr;">
          <div id="leftSection">
            <div id="profileSection" style="display: grid; grid-template-columns: 1fr 2fr; border: 1px solid gray; margin: 4px;">
              <div style="margin: 4px;">
                <a id="editProfileLink" style="margin-left: 60px; text-decoration: none;">edit profile</a>
                <img src="sampleAvartar.avif" alt="avartar" width="200" />
              </div>
              <div style="border: 1px solid gray; margin: 4px;">
                <p id="nickNameSection" style="border: 1px solid gray; margin: 16px;">PageManager is nick name section.</p>
                <p id="memoSection" style="border: 1px solid gray; margin: 16px;">PageManager is memo section.</p>
              </div>
            </div>
            <div id="gameHistorySection" style="border: 1px solid gray; margin: 4px;">gameHistorySection</div>
          </div>
          <div id="rightSection">
            <form action="" method="" id="userSearchBar" style="display: grid; grid-template-columns: 4fr 1fr; border: 1px solid gray; margin: 4px;">
              <input type="string" class="form-control" placeholder="user search bar" style="margin: 16px;" />
              <input type="submit" class="btn btn-info mb-3" value="search" style="margin: 16px;" />
            </form>
          </div>
        </div>`;

    bindEventToNavBar();

    const editProfileLink = document.getElementById("editProfileLink");
    editProfileLink.addEventListener("click", (event) => {
      event.preventDefault();
      clearBody();
      EditProfilePage.renderAndPushHistory();
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
}
