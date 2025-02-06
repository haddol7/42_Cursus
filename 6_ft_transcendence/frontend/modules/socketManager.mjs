import { PageManager } from "./page/manager.mjs";
import { GameLobbyPage } from "./page/gamelobby.mjs";
import { GameQueuePage } from "./page/gameQueue.mjs";

export class SocketManager {
  static socket = null;
  static roomList = null;
  static participantList = null;
  static maxNumOfParticipant = null;

  static connect = () => {
    SocketManager.socket = io("/", {
      auth: {
        user_id: 4242,
        user_name: "temp name",
      },
      path: "/room-sio/",
    });
    SocketManager.socket.on("connect", () => {
      console.log("successfully connected!!!");
    });
    SocketManager.onRoomListEvent();
    SocketManager.onRoomChangedEvent();
    // if (SocketManager.socket.ok) {
    // } else throw new Error("socket connection error");
  };

  static disconnect = () => {
    if (SocketManager.socket !== null) {
      SocketManager.socket.disconnect();
      SocketManager.socket = null;
      SocketManager.roomList = null;
      SocketManager.participantList = null;
      SocketManager.maxNumOfParticipant = null;
    }
  };

  static onRoomListEvent = () => {
    SocketManager.socket.on("room_list", (list) => {
      console.log(list);
      SocketManager.roomList = list;

      if (
        PageManager.currentpageStatus.page ===
        PageManager.pageStatus.gameLobby.page
      )
        GameLobbyPage.updateGameLobbySection(SocketManager.roomList);
    });
  };

  static onRoomChangedEvent = () => {
    SocketManager.socket.on("room_changed", (list) => {
      console.log(list);
      SocketManager.participantList = list;

      if (
        PageManager.currentpageStatus.page ===
        PageManager.pageStatus.gameQueue.page
      )
        GameQueuePage.updateQueueMemberSection();
    });
  };

  static emitMakeRoom = (roomName, roomLimit) => {
    SocketManager.socket.emit("make_room", {
      room_name: roomName,
      room_limit: roomLimit,
    });
  };

  static emitEnterRoom = (roomId) => {
    SocketManager.socket.emit("enter_room", { room_id: roomId });
  };

  static emitLeaveRoom = () => {
    SocketManager.socket.emit("leave_room");
    SocketManager.participantList = null;
    SocketManager.maxNumOfParticipant = null;
  };

  static getNumOfParticipants = () => {
    if (SocketManager.participantList === null)
      throw new Error("you should enter the room before request");
    else return SocketManager.participantList.people.length;
  };
}
