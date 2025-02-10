import { RoomSocketManager } from "../socketManager.mjs";

export class TournamentPage {
  static render = () => {
    console.log(RoomSocketManager.isOperator);
    if (RoomSocketManager.isOperator === true)
      RoomSocketManager.emitStartGame();
  };
}
