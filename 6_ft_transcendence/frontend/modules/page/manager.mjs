import { clearBody, removeBodyProperty } from "./lowRankElements.mjs";
import { RoomSocketManager } from "../socketManager.mjs";
import { LoginPage } from "./login.mjs";
import { MainPage } from "./main.mjs";
import { MyPage } from "./my.mjs";
import { EditProfilePage } from "./editProfile.mjs";
import { DashBoardPage } from "./dashboard.mjs";
import { GameLobbyPage } from "./gamelobby.mjs";
import { FriendPage } from "./friend.mjs";

export class PageManager {
  static currentpageStatus = null;

  static pageStatus = {
    login: { page: "loginPage" },
    twoFA: { page: "twoFAPage" },
    main: { page: "mainPage" },
    my: { page: "myPage" },
    friend: { page: "friendPage" },
    editProfile: { page: "editProfilePage" },
    dashBoard: { page: "dashBoardPage" },
    gameLobby: { page: "gameLobbyPage" },
    gameQueueCreation: { page: "gameQueueCreation" },
    gameQueue: { page: "gameQueue" },
    pong: { page: "pong" },
    aiMatch: { page: "aiMatch" },
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
      RoomSocketManager.disconnect();
      GameLobbyPage.renderAndPushHistory();
      return;
    }
    if (
      PageManager.currentpageStatus?.page === PageManager.pageStatus.pong.page
    ) {
      // 추후 게임 소켓 연결을 해제하는 코드가 들어가야 함
      GameLobbyPage.renderAndPushHistory();
      return;
    }
    if (
      PageManager.currentpageStatus?.page ===
      PageManager.pageStatus.aiMatch.page
    ) {
      // 추후 ai 게임 소켓 연결을 해제하는 코드가 들어가야 함
      GameLobbyPage.renderAndPushHistory();
      return;
    }
    if (
      PageManager.currentpageStatus?.page ===
      PageManager.pageStatus.gameQueue.page
    ) {
      RoomSocketManager.emitLeaveRoom();
      RoomSocketManager.disconnect();
      GameLobbyPage.renderAndPushHistory();
      return;
    }
    if (
      PageManager.currentpageStatus?.page ===
      PageManager.pageStatus.gameLobby.page
    )
      RoomSocketManager.disconnect();

    switch (event.state.page) {
      case PageManager.pageStatus.login.page:
        LoginPage.render();
        break;
      case PageManager.pageStatus.main.page:
        MainPage.render();
        break;
      case PageManager.pageStatus.my.page:
        MyPage.render();
        break;
      case PageManager.pageStatus.friend.page:
        FriendPage.render();
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
