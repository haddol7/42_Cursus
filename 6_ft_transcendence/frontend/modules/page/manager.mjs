import {
  clearBody,
  clearExceptNavBar,
  removeBodyProperty,
} from "./lowRankElements.mjs";
import { RoomSocketManager } from "../socketManager.mjs";
import { LoginPage } from "./login.mjs";
import { MainPage } from "./main.mjs";
import { MyPage } from "./my.mjs";
import { EditProfilePage } from "./editProfile.mjs";
import { DashBoardPage } from "./dashboard.mjs";
import { GameLobbyPage } from "./gamelobby.mjs";
import { FriendPage } from "./friend.mjs";
import { gameSocketDisconnect } from "../../game/client.js";

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
  };

  static popStateEvent(event) {
    switch (event.state.page) {
      case PageManager.pageStatus.login.page:
        clearBody();
        removeBodyProperty();
        break;
      case PageManager.pageStatus.main.page:
      case PageManager.pageStatus.my.page:
      case PageManager.pageStatus.friend.page:
      case PageManager.pageStatus.editProfile.page:
      case PageManager.pageStatus.dashBoard.page:
      case PageManager.pageStatus.gameLobby.page:
        clearExceptNavBar();
        break;
    }

    if (
      PageManager.currentpageStatus?.page ===
      PageManager.pageStatus.gameQueueCreation.page
    ) {
      RoomSocketManager.disconnect();
      GameLobbyPage.renderAndPushHistory();
      return;
    }
    if (
      PageManager.currentpageStatus?.page ===
        PageManager.pageStatus.pong.page ||
      PageManager.currentpageStatus?.page ===
        PageManager.pageStatus.aiMatch.page
    ) {
      gameSocketDisconnect();
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
