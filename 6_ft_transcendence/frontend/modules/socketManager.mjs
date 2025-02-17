import { PageManager } from "./page/manager.mjs";
import { GameLobbyPage } from "./page/gamelobby.mjs";
import { GameQueuePage } from "./page/gameQueue.mjs";
import { runPongGame } from "../game/client.js";
import { JWT } from "./authentication/jwt.mjs";

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
      console.log("successfully connected!!!");
    });
    RoomSocketManager.#onDisconnect();
    RoomSocketManager.#onRoomListEvent();
    RoomSocketManager.#onRoomChangedEvent();
    RoomSocketManager.#onStartGame();
    RoomSocketManager.socket.on("error", (error) => {
      console.error(error.toString());
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
      console.log(list);
      RoomSocketManager.roomList = list;

      if (
        PageManager.currentpageStatus.page ===
        PageManager.pageStatus.gameLobby.page
      ) {
        console.log(RoomSocketManager.roomList);
        GameLobbyPage.updateGameLobbySection(RoomSocketManager.roomList);
      }
    });
  };

  static #onRoomChangedEvent = () => {
    RoomSocketManager.socket.on("room_changed", (list) => {
      console.log(list);
      RoomSocketManager.participantList = list;

      if (
        PageManager.currentpageStatus.page ===
        PageManager.pageStatus.gameQueue.page
      ) {
        console.log(RoomSocketManager.participantList);
        GameQueuePage.updateQueueMemberSection();
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
      console.log(
        `Error occured.\nCode: ${response.code}\nText: ${response.text}`
      );
  };
}
