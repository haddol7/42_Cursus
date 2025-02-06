import { clearBody, removeBodyProperty } from "./lowRankElements.mjs";
import { SocketManager } from "../socketManager.mjs";
import { LoginPage } from "./login.mjs";
import { MainPage } from "./main.mjs";
import { MyPage } from "./my.mjs";
import { EditProfilePage } from "./editProfile.mjs";
import { DashBoardPage } from "./dashboard.mjs";
import { GameLobbyPage } from "./gamelobby.mjs";

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
    gameQueueCreation: { page: "gameQueueCreation" },
    gameQueue: { page: "gameQueue" },
    error: { page: "error" },
  };

  static popStateEvent(event) {
    if (
      PageManager.currentpageStatus?.page === PageManager.pageStatus.error.page
    ) {
      history.forward();
      return;
    }

    clearBody();
    removeBodyProperty();

    if (
      PageManager.currentpageStatus?.page ===
      PageManager.pageStatus.gameQueueCreation.page
    ) {
      GameLobbyPage.renderAndPushHistory();
      GameLobbyPage.updateGameLobbySection(SocketManager.roomList);
      return;
    }
    if (
      PageManager.currentpageStatus?.page ===
      PageManager.pageStatus.gameQueue.page
    ) {
      SocketManager.emitLeaveRoom();
      GameLobbyPage.renderAndPushHistory();
      GameLobbyPage.updateGameLobbySection(SocketManager.roomList);
      return;
    }

    if (
      PageManager.currentpageStatus?.page ===
      PageManager.pageStatus.gameLobby.page
    )
      SocketManager.disconnect();

    switch (event.state.page) {
      case PageManager.pageStatus.login.page:
        LoginPage.render();
        break;
      case PageManager.pageStatus.twoFA.page:
        history.back();
        break;
      case PageManager.pageStatus.main.page:
        MainPage.render();
        break;
      case PageManager.pageStatus.my.page:
        MyPage.render();
        break;
      case PageManager.pageStatus.editProfile.page:
        EditProfilePage.render();
        break;
      case PageManager.pageStatus.dashBoard.page:
        DashBoardPage.render();
        break;
      case PageManager.pageStatus.gameLobby.page:
        GameLobbyPage.render();
        break;
    }
  }
}
