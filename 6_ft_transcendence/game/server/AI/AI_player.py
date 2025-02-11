import neat
import socketio
import pickle
import time
import numpy as np
import sys

SERVER_URL = "http://localhost:3000"

global g_paddle_x
g_paddle_x = 0

# AI는 항상 paddle2로 설정합니다. -> AI 서버에서 설정할 예정

#서버에서 데이터를 받아오지 못할 때, 마지막으로 받은 데이터를 이용하여 예측
def predict_ball_position(ball_data):
    global g_paddle_x
    ball_x = ball_data["x"]
    ball_y = ball_data["y"]
    vx = ball_data["vx"]
    vy = ball_data["vy"]

    predicted_x = ball_x + vx
    predicted_y = ball_y + vy
    if (predicted_x >= 4.8 or predicted_x <= -4.8):
        vx = -vx
    elif (predicted_y >= 6.6 or predicted_y <= -6.6):
        vy = -vy * 1.05
        vx = vx * 1.05

    if (abs(vy) > 0.2):
        vy = 0.2 if vy > 0 else -0.2
    
    return {"x": predicted_x, "y": predicted_y, "vx": vx, "vy": vy, "AI_pos": g_paddle_x}

def run_trained_ai(room_id):
    global g_paddle_x

    with open("server/AI/data.pkl", "rb") as f:
        best_genome = pickle.load(f)

    config_path = "server/AI/config-feedforward"
    config = neat.Config(
        neat.DefaultGenome,
        neat.DefaultReproduction,
        neat.DefaultSpeciesSet,
        neat.DefaultStagnation,
        config_path,
    )
    net = neat.nn.FeedForwardNetwork.create(best_genome, config)

    try:
        sio = socketio.Client(reconnection=False)
    except Exception as e:
        print(f"⚠️ AI 클라이언트 생성 실패: {e}")
        return

    paddle_id = None
    last_update_time = 0
    last_ball_data = None
    
    @sio.event
    def connect():
        sio.emit("roomId", {"roomId": room_id, "isAIMode": False})

    @sio.event
    def init(data):
        nonlocal paddle_id
        paddle_id = data["paddleId"]

    @sio.event
    def updateBall(ball_data):
        global g_paddle_x
        nonlocal last_ball_data, last_update_time
        
        if not sio.connected or paddle_id is None:
            return
        
		#받아오는 데이터가 없을 때, 예측
        current_time = time.time()
        if current_time - last_update_time < 1.0:
            last_ball_data = predict_ball_position(last_ball_data)
        else:
            last_ball_data = ball_data
            last_update_time = current_time
        
        try:
            norm_x = (last_ball_data["x"] / 2.5)
            norm_y = (last_ball_data["y"] / 3.5)
            paddle_x = last_ball_data["AI_pos"]
            norm_paddle_x = (paddle_x / 2.5)
            
            move = ai_decide(net, norm_paddle_x, norm_x, norm_y)
            g_paddle_x = paddle_x + move * 0.075  

            sio.emit("paddleMove", {"paddleId": paddle_id, "paddleDirection": move})

        except Exception as e:
            print(f"⚠️ AI 오류: {e}")

    @sio.event
    def hitPaddle(data):
        pass

    @sio.event
    def gameOver(data):
        sio.disconnect()

    @sio.event
    def disconnect():
        pass
	
    def ai_decide(network, paddle_x, ball_x, ball_y):
        output = network.activate((paddle_x, ball_x, ball_y))
        decision = np.argmax(output)
        return [-1, 0, 1][decision]

    try:
        sio.connect(SERVER_URL, transports=["websocket"])
        time.sleep(0.1)
        sio.wait()
    except Exception as e:
        print(f"❌ AI 서버 연결 실패: {e}")

if __name__ == "__main__":    
    if len(sys.argv) < 2:
        sys.exit(1)
    
    room_id = sys.argv[1]
    run_trained_ai(room_id)
