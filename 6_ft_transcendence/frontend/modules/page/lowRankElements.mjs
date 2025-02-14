import { MainPage } from "./main.mjs";
import { MyPage } from "./my.mjs";
import { DashBoardPage } from "./dashboard.mjs";
import { GameLobbyPage } from "./gamelobby.mjs";
import { logout } from "../authentication/logout.mjs";
import { RoomSocketManager } from "../socketManager.mjs";
import { PageManager } from "./manager.mjs";

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

// 로그인 페이지와 2fa 인증 페이지의 렌더링에 사용되는 박스를 렌더
export const renderCentralBox = () => {
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

export const renderNavBar = () => {
  document.body.innerHTML = `
    <a id="title" class="nav justify-content-center home"><h1>Mighty Pong Contest</h1></a>
    <a id="logoutLink" class="nav justify-content-center sublink">logout</a>
    <hr />
    <ul class="nav justify-content-center">
      <li class="nav-item">
        <a id="myPageLink" class="nav-link sublink">My Page</a>
      </li>
      <li class="nav-item">
        <a id="dashBoardLink" class="nav-link sublink">Dash Board</a>
      </li>
      <li class="nav-item">
        <a id="gameLobbyLink" class="nav-link sublink">Game Lobby</a>
      </li>
    </ul>
    <hr />`;
};

export const bindEventToNavBar = () => {
  const title = document.getElementById("title");
  const logoutLink = document.getElementById("logoutLink");
  const myPageLink = document.getElementById("myPageLink");
  const dashBoardLink = document.getElementById("dashBoardLink");
  const gameLobbyLink = document.getElementById("gameLobbyLink");

  title.addEventListener("click", (event) => {
    if (
      PageManager.currentpageStatus.page !== PageManager.pageStatus.main.page
    ) {
      event.preventDefault();
      console.log("go to main page!!!");
      clearBody();

      if (
        PageManager.currentpageStatus.page ===
        PageManager.pageStatus.gameLobby.page
      )
        RoomSocketManager.disconnect();

      MainPage.renderAndPushHistory();
    }
  });

  logoutLink.addEventListener("click", (event) => {
    event.preventDefault();
    clearBody();

    if (
      PageManager.currentpageStatus.page ===
      PageManager.pageStatus.gameLobby.page
    )
      RoomSocketManager.disconnect();

    logout();
  });

  myPageLink.addEventListener("click", (event) => {
    if (PageManager.currentpageStatus.page !== PageManager.pageStatus.my.page) {
      event.preventDefault();
      clearBody();

      if (
        PageManager.currentpageStatus.page ===
        PageManager.pageStatus.gameLobby.page
      )
        RoomSocketManager.disconnect();

      MyPage.renderAndPushHistory();
    }
  });

  dashBoardLink.addEventListener("click", (event) => {
    if (
      PageManager.currentpageStatus.page !==
      PageManager.pageStatus.dashBoard.page
    ) {
      event.preventDefault();
      clearBody();

      if (
        PageManager.currentpageStatus.page ===
        PageManager.pageStatus.gameLobby.page
      )
        RoomSocketManager.disconnect();

      DashBoardPage.renderAndPushHistory();
    }
  });

  gameLobbyLink.addEventListener("click", (event) => {
    if (
      PageManager.currentpageStatus.page !==
      PageManager.pageStatus.gameLobby.page
    ) {
      event.preventDefault();
      clearBody();
      GameLobbyPage.renderAndPushHistory();
    }
  });
};
