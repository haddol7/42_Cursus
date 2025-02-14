import { RoomSocketManager } from "../socketManager.mjs";
import { PageManager } from "./manager.mjs";

export class PongPage {
  static play = () => {
    if (RoomSocketManager.isOperator === true)
      RoomSocketManager.emitStartGame();

    PageManager.currentpageStatus = PageManager.pageStatus.pong;
  };
}
