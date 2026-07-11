# Game-ai

## Endpoints

### POST /ai

- Request
    - `match_id`: `int`

Make an AI to participate `match_id`, and connect the AI to the match. Make a websocket connection and participate the match.

After this response says ok, player should also see the AI that is in the game, and play a game