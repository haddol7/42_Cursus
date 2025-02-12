# game

## WebSocket

### on connection

소켓 연결이 처음 이뤄진 상태입니다. 소켓 연결에 게임을 바로 시작하지는 않습니다.

하지만, 이미 하나의 게임에는 참여한 상태여야 합니다. 토너먼트가 시작한 후에 사용자는 소켓 연결을 요청할 수 있습니다.

### on paddleMove

- Request
```json
{
    "paddleId": "paddle1 | paddle2",
    "position": "float"
}
```

`paddleId`의 `position`을 받고, 그 정보를 게임하는 모든 사람에게 `updatePaddle`로 emit합니다.

### on nextGame

다음 게임에 참여합니다

### on disconnect

소켓 연결이 끊어진 상태입니다. 이때에는 서버에서 패배 처리 등 알맞은 처리를 합니다.

### emit init

- Response
```json
{
    "roomName": "string",
    "paddleId": "paddle1 | paddle2"
}
```

게임이 시작될 때 `roomName`과 `paddleId`를 전달합니다. `roomName`은 소켓에서 연결된 방 이름이고, 방을 구분하는 이름입니다.


### emit updateScore

- Response

```json
{
    "paddle1": "int",
    "paddle2": "int",
}
```

점수가 갱신된 경우 이 이벤트로 게임에 참가한 모든 사람에게 알립니다.

### emit updatePaddle

- Response

```json
{
    "paddleId": "paddle1 | paddle2",
    "position": "float"
}
```

`paddleMove`로 받은 position을 조정하여 다시 보냅니다. 당사자와 다른 사람에게도 같이 보냅니다.

게임하고 있는 모든 사람에게 같이 보냅니다.

### emit updateBall

- Response

```json
{
    "x": "float",
    "y": "float",
    "vx": "float",
    "vy": "float"
}
```

공의 위치를 계속 보냅니다. 60fps 속도로 보낸다면 16ms에 한 번씩 정보를 계산해 보냅니다.


### emit gameOver

- Response

```json
{
    "winner": "paddle1 | padddle2"
}
```

이긴 사람을 판단해 모든 게임에 참가중인 사람에게 보냅니다.

### emit resetPositions

- Response

```json
{
    "ball": {
        "x": "float",
        "y": "float",
        "vx": "float",
        "vy": "float"
    },
    "paddles": {
        "paddle1": "float",
        "paddle2": "float"
    }
}
```

게임 초기 설정을 클라이언트에게 보냅니다. 점수를 낸 후 다음 게임을 시작할 때 보냅니다.

### emit playerLeft 

## Endpoint

### POST /_internal/game

```json
{
    "room_name": "string",
    "users": [{
        "user_id": "int",
        "user_name": "string"
    }]
}
```

In this url, the list of `users` will be randomly permutated. As the result, 1-2, 3-4, and so on will be matched.

The sender of this request has responsibility of sending response to users to join the room. This endpoint will send response whether it has created room succesfully so that user can connect to this game or it has not created successfully in case of error happened.

When internal server receives an error, the server should handle it properly. As the result, the game may not be started correctly.

This endpoint will not check the user exists or not. Such validation should have be done when the request was made.

- If one of the user is already in the other room: `user.already_joined` (400)
- If the list length is not in the accepted value: `bad_request:users` (400)
- If the value of `room_name` already exists: `bad_request:room_name` (400)
- Otherwise in case of internal error: `internal_error` (500)

### POST /_internal/aigame

```json
{
    "user": {
        "user_id": "int",
        "user_name": "string"
    }
}
```

Specify one user to do a practice match with ai. The user should not be one of the match already, and the user will be in the practice match when the user connects to the match. The match with ai will be started immediately.

## Pseudocode

### on connect

- If user is not list in user of match, connectionrefusederror
- match <- user's match
- if match has two participants online, start game
- if the opponent is not yet connected, wait for `TIMEOUT` seconds
    - If the time ends, end game with the player's win and wait for next match event
- if the opponent is already disconnected, emit win event and wait for next match event

### on disconnect

- If the user is not in the game, safely disconnect the user
- If the user is in the game, the game ends with opponent's win
- If the user is in the game but the opponent is not connected, the game ends with opponent's win

## To User Backend

### POST /_internal/dashboard

- Request


```json
{
  "player1_id": "int",
  "player2_id": "int",
  "player1_score" : "int, obtained score",
  "player2_score" : "int, obtained score",
  "winner_id" : "int, winner's id, will be one of player1_id and player2_id",
  "match_date" : "date", // ex) "2025-02-10T14.30:00Z"
  "play_time" : "int, in seconds"
}
```

게임이 끝날 때마다 보냅니다.
