# Websocket

## connect

소켓에 연결할 때 이벤트가 자동으로 발생합니다.

연결된 소켓에 바로 `room_list` 이벤트를 emit합니다.

(임시적으로) `auth: {user_id: int, user_name: string}`을 넘겨주어야 합니다. 추후, `jwt`로 바꿀 예정입니다.

- 이미 연결된 `user_id`인 경우, `ConnectionRefusedError("user_found")`

## disconnect

소켓에 연결 해제될 때 자동으로 발생합니다.

연결된 소켓에 (있다면) 연결된 방을 해제하고, 방에 있던 사람에게 변동사항을 알려줍니다.

## event.on: make_room

`{room_name: string, room_limit: int}`를 넘겨주어야 합니다. `room_limit`은 2, 4, 8, 16 중 하나여야 합니다.

방에 참여하지 않은 사람에게는 `room_list` 이벤트를 emit합니다.

방에 참여한 후에는, 참여한 사람에게 `room_changed` 이벤트를 emit합니다.

방에 참여한 후에는, 더이상 `room_list` 이벤트는 emit받지 않습니다.

- 필드가 적절하지 않은 경우, `BadRequestFieldException("room_name")`, `BadRequestFieldException("room_limit")`
- 이미 방에 참가해 있는 경우, `WebSocketAlreadyRoomJoinedException()`

## event.on: enter_room

`{room_id: string}`을 넘겨주어야 합니다. 더이상 `room_list` 이벤트는 emit받지 않습니다.

- 필드가 적절하지 않은 경우, `BadRequestFieldException("room_id")`
- 이미 (어떤 것이든) 방에 참가해 있는 경우, `WebSocketAlreadyRoomJoinedException()`
- 방에 참가할 수 없는 경우, `WebSocketRoomNotFoundException()`
- 방이 꽉 찬 경우, `WebSocketRoomFullException()`

## event.on: leave_room

데이터를 받지 않습니다. (넘겨주어서는 안 됩니다.)

현재 참가해있는 방에서 나가고, 다시 `room_list`를 emit받는 상태로 돌아갑니다. 방에서 나간 직후, `room_list` 이벤트를 한 번 emit받습니다.

- 방에 참가해있지 않는 경우, `WebSocketRoomNotJoinedException()`


## event.on: start_game

게임을 시작합니다. 데이터를 받지 않습니다.

- 방에 참가하지 않은 경우, `WebSocketRoomNotJoinedException()`
- 방이 다 차지 않은 경우, `WebSocketRoomNotFullException()`
- 방에서 관리자가 아닌 경우, `WebSocketRoomNotAdminException()`

## event.on: debug

현재 참가해있는 방을 보여줍니다. 디버그용이고, 쓰이지 않습니다.

## event.emit: room_list

방의 현재 상태가 변경되었을 때 emit합니다. 처음으로 이 이벤트를 받는 대상이 되었을 때에도 emit받습니다.

```json
{
    "room": [
        {
            "room_id": "string",
            "room_name": "string",
            "room_limit": "int",
            "room_cur_people": "int"
        }
    ]
}
```

## event.emit: room_changed

방의 사람 수가 변동되었을 때 emit합니다. 처음으로 이 이벤트를 받는 대상이 되었을 때에도 emit받습니다.

맨 첫 번째 사람이 관리자입니다. 관리자가 나가면, 배열의 바로 다음 사람이 관리자가 됩니다.

```json
{
    "people": [
        {
            "user_id": "int",
            "user_name": "string"
        }
    ]
}
```

# TEST

미약하지만, 테스트도 존재합니다. 실행시킨 이후, `http://localhost:7600/static/index.html`을 이용해 각 이벤트를 발생시키고 이벤트가 emit되었을 때 `console.log()`도 볼 수 있습니다.

`/static/index.html` 파일에서 적용된 코드를 볼 수 있고, 각 버튼이 이벤트 발생에 대응됩니다.

참고로, `127.0.0.1`과 `localhost`는 여기에서 전혀 다릅니다. `127.0.0.1`로 실행한다면 재미있는 로그를 볼 수 있을텐데, 이것도 [공부해볼만한 내용](https://evan-moon.github.io/2020/05/21/about-cors/)입니다.