import { PageManager } from "./page/manager.mjs";
import { GameLobbyPage } from "./page/gamelobby.mjs";
import { GameQueuePage } from "./page/gameQueue.mjs";
import { runPongGame } from "../game/client.js";
import { JWT } from "./authentication/jwt.mjs";
import { logout } from "./authentication/logout.mjs";
import { MainPage } from "./page/main.mjs";
import { clearExceptNavBar } from "./page/lowRankElements.mjs";
import { LOGIN_EXPIRED_MSG } from "./authentication/globalConstants.mjs";

export class RoomSocketManager {
  static socket = null;
  static roomList = null;
  static participantList = null;
  static maxNumOfParticipant = null;
  static isOperator = false;

  static connect = () => {
    RoomSocketManager.socket = io("/", {
      auth: {
        jwt: JWT.getJWTTokenFromCookie().accessToken,
      },
      path: "/room-sio/",
    });
    RoomSocketManager.socket.on("connect", () => {
      alert("게임 로비에 연결되었습니다.");
    });
    RoomSocketManager.#onDisconnect();
    RoomSocketManager.#onRoomListEvent();
    RoomSocketManager.#onRoomChangedEvent();
    RoomSocketManager.#onStartGame();
    RoomSocketManager.socket.on("connect_error", async (error) => {
      alert("게임 로비에 연결 중 문제가 발생하였습니다.");
      alert("재연결을 시도합니다.");
      if (error.message === "jwt.expired") {
        try {
          await JWT.getNewToken();
          RoomSocketManager.connect();
        } catch (e) {
          alert(`${LOGIN_EXPIRED_MSG}(${e})`);
          logout();
        }
      } else {
        alert(`재연결에 실패하였습니다. 메인 페이지로 이동합니다(${error})`);
        RoomSocketManager.#whenDisconnect();
        clearExceptNavBar();
        MainPage.renderAndPushHistory();
      }
    });
  };

  static disconnect = () => {
    if (RoomSocketManager.socket !== null) {
      RoomSocketManager.socket.disconnect();
      RoomSocketManager.#whenDisconnect();
    }
  };

  static #onDisconnect = () => {
    RoomSocketManager.socket.on(
      "disconnect",
      RoomSocketManager.#whenDisconnect
    );
  };

  static #onRoomListEvent = () => {
    RoomSocketManager.socket.on("room_list", (list) => {
      RoomSocketManager.roomList = list;

      if (
        PageManager.currentpageStatus.page ===
        PageManager.pageStatus.gameLobby.page
      ) {
        GameLobbyPage.updateGameRoomList(RoomSocketManager.roomList);
      }
    });
  };

  static #onRoomChangedEvent = () => {
    RoomSocketManager.socket.on("room_changed", (list) => {
      RoomSocketManager.participantList = list;

      if (
        PageManager.currentpageStatus.page ===
        PageManager.pageStatus.gameQueue.page
      ) {
        GameQueuePage.updateQueueInfo();
      }
    });
  };

  static #onStartGame = () => {
    RoomSocketManager.socket.on("start_game", () => {
      RoomSocketManager.disconnect();
      document.body.innerHTML = `
        <div id="gameOverPopup">
          <div id="popupContent">
            <h2>게임 종료!</h2>
            <p id="gameResult"></p>
            <button id="restartButton">나가기</button>
          </div>
        </div>
      `;
      runPongGame();
    });
  };

  static emitMakeRoom = (roomName, roomLimit) => {
    RoomSocketManager.isOperator = true;
    RoomSocketManager.socket.emit(
      "make_room",
      {
        room_name: roomName,
        room_limit: roomLimit,
      },
      RoomSocketManager.#alertWhenError
    );
  };

  static emitEnterRoom = (roomId) => {
    RoomSocketManager.socket.emit(
      "enter_room",
      { room_id: roomId },
      RoomSocketManager.#alertWhenError
    );
  };

  static emitLeaveRoom = () => {
    RoomSocketManager.socket.emit(
      "leave_room",
      null,
      RoomSocketManager.#alertWhenError
    );
    RoomSocketManager.participantList = null;
    RoomSocketManager.maxNumOfParticipant = null;
  };

  static emitStartGame = () => {
    RoomSocketManager.socket.emit(
      "start_game",
      null,
      RoomSocketManager.#alertWhenError
    );
  };

  static #whenDisconnect = () => {
    RoomSocketManager.socket = null;
    RoomSocketManager.roomList = null;
    RoomSocketManager.participantList = null;
    RoomSocketManager.maxNumOfParticipant = null;
  };

  static getNumOfParticipants = () => {
    if (RoomSocketManager.participantList === null)
      throw new Error("you should enter the room before request");
    else return RoomSocketManager.participantList.people.length;
  };

  static #alertWhenError = (response) => {
    if ("error" in response)
      alert(`Error occured.\nCode: ${response.code}\nText: ${response.text}`);
  };
}
