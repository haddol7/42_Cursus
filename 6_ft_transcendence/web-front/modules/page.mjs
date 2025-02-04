import { CLIENT_ID, logout, JWT, TwoFA } from "./authentication.mjs";
import { replaceAllScriptChar } from "./security.mjs";

// body의 모든 자식 요소들을 제거
export const clearBody = () => {
  document.body.innerHTML = "";
};

// 박스를 중앙 정렬하기 위해 body에 부여했던 속성을 초기화한다.
export const removeBodyProperty = () => {
  document.body.style.removeProperty("display");
  document.body.style.removeProperty("justify-content");
  document.body.style.removeProperty("align-items");
  document.body.style.removeProperty("height");
};

export class PageManager {
  static currentpageStatus = null;

  static pageStatus = {
    login: { page: "loginPage" },
    twoFA: { page: "twoFAPage" },
    main: { page: "mainPage" },
    my: { page: "myPage" },
    editProfile: { page: "editProfilePage" },
    dashBoard: { page: "dashBoardPage" },
    gameLobby: { page: "gameLobbyPage" },
    error: { page: "error" },
  };

  static popStateEvent(event) {
    if (
      PageManager.currentpageStatus?.page === PageManager.pageStatus.error.page
    )
      return;

    clearBody();
    removeBodyProperty();

    switch (event.state.page) {
      case PageManager.pageStatus.login.page:
        LoginPage.renderLoginPage();
        break;
      case PageManager.pageStatus.twoFA.page:
        history.back();
        break;
      case PageManager.pageStatus.main.page:
        MainPage.renderMainPage();
        break;
      case PageManager.pageStatus.my.page:
        MyPage.renderMyPage();
        break;
      case PageManager.pageStatus.editProfile.page:
        EditProfilePage.renderEditProfilePage();
        break;
      case PageManager.pageStatus.dashBoard.page:
        DashBoardPage.renderDashBoardPage();
        break;
      case PageManager.pageStatus.gameLobby.page:
        GameLobbyPage.renderGameLobbyPage();
        break;
    }
  }
}

// 로그인 페이지와 2fa 인증 페이지의 렌더링에 사용되는 박스를 렌더
const renderCentralBox = () => {
  document.body.style.height = "100vh";
  document.body.style.display = "flex";
  document.body.style.justifyContent = "center";
  document.body.style.alignItems = "center";

  document.body.innerHTML = `<div class="card text-bg-success mb-3" style="max-width: 18rem;">
    <div class="card-header">42 Transcendence</div>
    <div class="card-body">
        <h5 class="card-title">Mighty Pong Contest</h5>
        <p class="card-text">Welcome to 42 mighty pong contest!!</p>
    </div>
</div>`;

  const cardBody = document.getElementsByClassName("card-body")[0];

  return cardBody;
};


export class LoginPage {
  // 로그인 페이지를 화면에 렌더링한다.
  static renderLoginPage() {
    const centralBox = renderCentralBox();

    if (JWT.getJWTTokenFromCookie() === null) {
      const linkTo42Oauth = document.createElement("a");

      linkTo42Oauth.classList.add(..."btn btn-info".split(" "));
      linkTo42Oauth.textContent = "42Oauth";

      centralBox.appendChild(linkTo42Oauth);

      linkTo42Oauth.onclick = (event) => {
        event.preventDefault();
        window.location.href =
          "https://api.intra.42.fr/oauth/authorize" +
          `?client_id=${CLIENT_ID}` +
          `&redirect_uri=${window.location.href}` +
          "&response_type=code";
      };
    } else {
      const linkToMainPage = document.createElement("a");

      linkToMainPage.classList.add(..."btn btn-info".split(" "));
      linkToMainPage.textContent = "return to main page";
      centralBox.appendChild(linkToMainPage);

      linkToMainPage.onclick = (event) => {
        event.preventDefault();
        removeBodyProperty();
        clearBody();
        MainPage.renderMainPageWithPushHistory();
      };
      const logoutButton = document.createElement("a");

      logoutButton.classList.add(..."btn btn-info".split(" "));
      logoutButton.textContent = "logout";
      centralBox.appendChild(logoutButton);

      logoutButton.onclick = (event) => {
        event.preventDefault();
        logout();
      };
    }

    PageManager.currentpageStatus = PageManager.pageStatus.login;
  }

  // 히스토리를 갱신하며 로그인 페이지를 화면에 렌더링한다.
  static renderLoginPageWithPushHistory(/* 차후 42 oauth 페이지로의 url을 매개변수로 받아야 함 */) {
    LoginPage.renderLoginPage();
    history.pushState(PageManager.pageStatus.login, "");
  }

  static renderLoginPageWithReplaceHistory() {
    LoginPage.renderLoginPage();
    history.replaceState(PageManager.pageStatus.login, "");
  }

  // 로그인 페이지를 화면에서 지운다.
  static destroyLoginPage() {
    removeBodyProperty();
    clearBody();
  }
}

export class TwoFAPage {
  static renderTwoFAPageWithReplaceHistroy(url) {
    const centralBox = renderCentralBox();

    centralBox.innerHTML += `
      <form id="twoFAUserNameForm" action="" method="">
        <input id="otpUserNameInput" type="password" class="form-control" placeholder="please input OTP user name" />
        <input id="otpUserNameSubmit" type="submit" class="btn btn-info mb-3" value="submit" />
      </form>
    `;

    document.getElementById("twoFAUserNameForm").onsubmit = async (event) => {
      event.preventDefault();

      const otpUserName = replaceAllScriptChar(event.target.getElementById("otpUserNameInput").value);
      
      console.log(otpUserName);
      
      const otpUrl = await TwoFA.sendOTPUserNameToServer(
        JWT.getJWTTokenFromCookie().accessToken,
        otpUserName
      );

      console.log(otpUrl);

      const twoFAForm = document.getElementById("twoFAUserNameForm");
      twoFAForm.innerHTML = "";
      twoFAForm.parentNode.removeChild(twoFAForm);

      centralBox.innerHTML += `
        <form id="twoFAOTPCodeForm" action="" method="">
          <input id="otpCodeInput" type="password" class="form-control" placeholder="please input otp code" />
          <input id="otpCodeSubmit" type="submit" class="btn btn-info mb-3" value="submit" />
        </form>
      `;

      document.getElementById("twoFAOTPCodeForm").onsubmit = async (event) => {
        event.preventDefault();
        const otpCode = replaceAllScriptChar(document.getElementById("otpCodeInput").value);

        console.log(otpCode);

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

    PageManager.currentpageStatus = PageManager.pageStatus.twoFA;
    history.replaceState(PageManager.pageStatus.twoFA, "", url);
  }

  static sendOTPCodeWhileResponseOk = async (otpCode) => {
    let response = await TwoFA.sendOTPCodeToServer(
      JWT.getJWTTokenFromCookie().accessToken,
      otpCode
    );
    if (response.ok) {
      TwoFAPage.destroyTwoFAPage();
      MainPage.renderMainPageWithPushHistory();
    } else {
      const text = await response.text();
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
              JWT.getNewToken();
              sendOTPCodeWhileResponseOk();
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

  static destroyTwoFAPage() {
    removeBodyProperty();
    clearBody();
  }
}

const renderNavBar = () => {
  document.body.innerHTML = `
  <a id="title" class="nav justify-content-center" style="color:green; text-decoration: none;"><h1>Mighty Pong Contest</h1></a>
  <a id="logoutLink" class="nav justify-content-center" style="color:skyblue; text-decoration: none;">logout</a>
  <hr />
  <ul class="nav justify-content-center">
    <li class="nav-item">
      <a id="myPageLink" class="nav-link">My Page</a>
    </li>
    <li class="nav-item">
      <a id="dashBoardLink" class="nav-link">Dash Board</a>
    </li>
    <li class="nav-item">
      <a id="gameLobbyLink" class="nav-link">Game Lobby</a>
    </li>
  </ul>
  <hr />`;
};

const bindEventToNavBar = () => {
  const title = document.getElementById("title");
  const logoutLink = document.getElementById("logoutLink");
  const myPageLink = document.getElementById("myPageLink");
  const dashBoardLink = document.getElementById("dashBoardLink");
  const gameLobbyLink = document.getElementById("gameLobbyLink");

  title.addEventListener("click", (event) => {
    event.preventDefault();
    console.log("go to main page!!!");
    clearBody();
    MainPage.renderMainPageWithPushHistory();
  });

  logoutLink.addEventListener("click", (event) => {
    event.preventDefault();
    clearBody();
    logout();
    console.log("logout!!");
    LoginPage.renderLoginPageWithPushHistory();
  });

  myPageLink.addEventListener("click", (event) => {
    event.preventDefault();
    clearBody();
    MyPage.renderMyPageWithPushHistory();
  });

  dashBoardLink.addEventListener("click", (event) => {
    event.preventDefault();
    clearBody();
    DashBoardPage.renderDashBoardPageWithPushHistory();
  });

  gameLobbyLink.addEventListener("click", (event) => {
    event.preventDefault();
    clearBody();
    GameLobbyPage.renderGameLobbyPageWithPushHistory();
  });
};

class MainPage {
  static renderMainPage() {
    renderNavBar();
    bindEventToNavBar();
    PageManager.currentpageStatus = PageManager.pageStatus.main;
  }

  static renderMainPageWithPushHistory() {
    MainPage.renderMainPage();
    history.pushState(PageManager.pageStatus.main, "");
  }
}

class MyPage {
  static renderMyPage() {
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
      EditProfilePage.renderEditProfilePageWithPushHistory();
    });

    PageManager.currentpageStatus = PageManager.pageStatus.my;
  }

  static renderMyPageWithPushHistory() {
    MyPage.renderMyPage();
    history.pushState(PageManager.pageStatus.my, "");
  }

  static destroyMyPage() {
    const myPageSection = document.getElementById("mainPageSection");
    myPageSection.innerHTML = "";
    myPageSection.parentNode.removeChild(myPageSection);
  }
}

class EditProfilePage {
  static renderEditProfilePage() {
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
        <form action="" method="" id="editAvartarSection" style="border: 1px solid gray; margin: 4px;">
          <input type="file" class="form-control" placeholder="new avartar image" style="margin: 16px;" />
          <input type="string" class="form-control" placeholder="new nickname" style="margin: 16px;" />
          <input type="string" class="form-control" placeholder="new memo" style="margin: 16px;" />
          <input type="submit" class="btn btn-info mb-3" value="edit" style="margin: 16px;" />
        </form>
      </div>
    `;

    bindEventToNavBar();
    PageManager.currentpageStatus = PageManager.pageStatus.editProfile;
  }

  static renderEditProfilePageWithPushHistory() {
    EditProfilePage.renderEditProfilePage();
    history.pushState(PageManager.pageStatus.editProfile, "");
  }

  static destroyEditProfilePage() {
    const editProfileSection = document.getElementById("editProfileSection");
    editProfileSection.innerHTML = "";
    editProfileSection.parentNode.removeChild(editProfileSection);
  }
}

class DashBoardPage {
  static renderDashBoardPage() {
    renderNavBar();

    document.body.innerHTML += `
      <div id="dashBoardSection" style="border: 1px solid gray; margin: 4px;">dash board section</div>
    `;

    bindEventToNavBar();
    PageManager.currentpageStatus = PageManager.pageStatus.dashBoard;
  }

  static renderDashBoardPageWithPushHistory() {
    DashBoardPage.renderDashBoardPage();
    history.pushState(PageManager.pageStatus.dashBoard, "");
  }

  static destroyDashBoardPage() {
    const dashBoardSection = document.getElementById("dashBoardSection");
    dashBoardSection.innerHTML = "";
    dashBoardSection.parentNode.removeChild(dashBoardSection);
  }
}

class GameLobbyPage {
  static renderGameLobbyPage() {
    renderNavBar();

    document.body.innerHTML += `
      <div id="gameLobbySection" style="border: 1px solid gray; margin: 4px;">
        <div>
          <a id="gameQueueCreationLink" class="btn btn-info mb-3" style="margin: 4px;">make new game queue</a>
        </div>
        <div style="border: 1px solid gray; margin: 4px;">
          <a id="gameQueueLink" style="margin-left: 60px; text-decoration: none;">game queue link</a>
        </div>
      </div>
    `;

    bindEventToNavBar();

    const gameQueueCreationLink = document.getElementById(
      "gameQueueCreationLink"
    );
    gameQueueCreationLink.addEventListener("click", (event) => {
      event.preventDefault();
      clearBody();
      GameQueueCreationPage.renderGameQueueCreationPage();
    });

    const gameQueueLink = document.getElementById("gameQueueLink");
    gameQueueLink.addEventListener("click", (event) => {
      event.preventDefault();
      clearBody();
      GameQueuePage.renderGameQueuePage();
    });

    PageManager.currentpageStatus = PageManager.pageStatus.gameLobby;
  }

  static renderGameLobbyPageWithPushHistory() {
    GameLobbyPage.renderGameLobbyPage();
    history.pushState(PageManager.pageStatus.gameLobby, "");
  }

  static destroyGameLobbyPage() {
    const gameLobbySection = document.getElementById("gameLobbyScetion");
    gameLobbySection.innerHTML = "";
    gameLobbySection.parentNode.removeChild(gameLobbySection);
  }
}

class GameQueueCreationPage {
  static renderGameQueueCreationPage() {
    renderNavBar();

    document.body.innerHTML += `
      <div id="gameQueueCreationSection" style="border: 1px solid gray; margin: 4px;">
        <p style="margin: 4px;">Please select the number of members of PageManager Pong Tournament.</p>
        <form action="" method="" id="selectNumOfMembers">
          <label style="margin: 4px;">  
            <input type="radio" name="numOfMembers" value="2" /> 2
          </label><br />
          <label style="margin: 4px;">  
            <input type="radio" name="numOfMembers" value="4" /> 4
          </label><br />
          <label style="margin: 4px;">  
            <input type="radio" name="numOfMembers" value="8" /> 8
          </label><br />
          <label style="margin: 4px;">  
            <input type="radio" name="numOfMembers" value="16" /> 16
          </label><br />
          <label style="margin: 4px;">
            <input id="createQueueButton" type="submit" class="btn btn-info mb-3" value="create queue" />
          </label>
        </form>
      </div>
    `;

    const createQueueButton = document.getElementById("createQueueButton");
    const radioButtons = document.getElementsByName("numOfMembers");

    createQueueButton.disabled = true;

    radioButtons.forEach((rb) => {
      rb.addEventListener("click", () => {
        createQueueButton.disabled = false;
      });
    });

    createQueueButton.addEventListener("click", (event) => {
      event.preventDefault();
      clearBody();
      GameQueuePage.renderGameQueuePage();
    });
  }

  static destroyGameQueueCreationPage() {
    const gameQueueCreationSection = document.getElementById(
      "gameQueueCreationSection"
    );
    gameQueueCreationSection.innerHTML = "";
    gameQueueCreationSection.parentNode.removeChild(gameQueueCreationSection);
  }
}

class GameQueuePage {
  static renderGameQueuePage() {
    renderNavBar();

    document.body.innerHTML += `
      <div id="gameQueueSection" style="border: 1px solid gray; margin: 4px;">
        <p style="margin: 4px;">current members (1 / 4)</p>
        <div style="border: 1px solid gray; margin: 4px;">
          <p>member 1</p>
        </div>
        <a id="quitQueueLink" class="btn btn-info mb-3"; style="margin: 4px;" text-decoration: none;">Quit queue link</a>
      </div>
    `;

    const quitQueueLink = document.getElementById("quitQueueLink");
    quitQueueLink.addEventListener("click", (event) => {
      event.preventDefault();
      clearBody();
      GameLobbyPage.renderGameLobbyPageWithPushHistory();
    });
  }

  static destroyGameQueuePage() {
    const gameQueueSection = document.getElementById("gameQueueSection");
    gameQueueSection.innerHTML = "";
    gameQueueSection.parentNode.removeChild(gameQueueSection);
  }
}

// 아래의 두 페이지는 서버와의 통신이 가능해야 진입할 수 있기 때문에 일단 구현을 보류합니다.
class TournamentPage {}
class PongPage {}

export class ErrorPage {
  static renderErrorPage(errorCode) {
    removeBodyProperty();
    clearBody();

    document.body.innerHTML = `${errorCode}`;

    PageManager.currentpageStatus = PageManager.pageStatus.error;
    history.pushState(PageManager.pageStatus.error, "");
  }
}
