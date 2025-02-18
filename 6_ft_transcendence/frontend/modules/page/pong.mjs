import { RoomSocketManager } from "../socketManager.mjs";
import { PageManager } from "./manager.mjs";
import { activateScrollBar } from "./utility.mjs";

export class PongPage {
  static play = () => {
    if (RoomSocketManager.isOperator === true)
      RoomSocketManager.emitStartGame();

    activateScrollBar();
    PageManager.currentpageStatus = PageManager.pageStatus.pong;
  };
}
