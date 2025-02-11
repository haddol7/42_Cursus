import neat
import socketio
import time
import pickle
import random
import numpy as np

SERVER_URL = "http://localhost:3000"
generation = 0

def run_ai_instance(genome, config, genomde_id):
    try:
        sio = socketio.Client(reconnection=False)
    except Exception as e:
        print(f"⚠️ AI 클라이언트 생성 실패: {e}")
        return

    net = neat.nn.FeedForwardNetwork.create(genome, config)
    paddle_id = None
    fitness = 0.0
    last_move = 0
    previous_ball_x = 0
    hit_count = 0
    max_vx = 0.1

    @sio.event
    def connect():
        sio.emit("roomId", "4242")

    @sio.event
    def init(data):
        nonlocal paddle_id
        paddle_id = data["paddleId"]

    @ sio.event
    def updateBall(ball_data):
        nonlocal last_move, genome, previous_ball_x, max_vx
    
        if not sio.connected or paddle_id is None:
            return
        try:
            max_vx = max(max_vx, abs(ball_data["vx"]))
    
            norm_x = (ball_data["x"] / 2.5)  # 정규화 범위 조정
            norm_y = (ball_data["y"] / 3.5)
            paddle_x = ball_data.get("AI_pos", 0.0)
            norm_paddle_x = (paddle_x / 2.5)
    
            ball_x = ball_data["x"]
    
            if random.uniform(0, 1) < 0.02:
                move = random.choice([-1, 0, 1])
            else:
                move = ai_decide(net, norm_paddle_x, norm_x, norm_y)

            previous_distance = abs(previous_ball_x - paddle_x)
            current_distance = abs(ball_x - paddle_x)
    
            if move != 0:
                sio.emit("paddleMove", {"paddleId": paddle_id, "paddleDirection": move})
    
                if ball_data["vy"] > 0 and current_distance < previous_distance:  # vy < 0 이면 공이 내려오는 중
                    genome.fitness += 0.2  # 공이 내려올 때 거리 감소 → 보상 증가
                elif ball_data["vy"] > 0 and current_distance > previous_distance:
                    genome.fitness -= 0.01  # 공과의 거리가 증가 → 패널티
    
                # 같은 방향 연속 움직임 패널티
                if move == last_move:
                    genome.fitness -= 0.03  
                last_move = move

                # 벽에 닿는 경우 패널티
                if (paddle_x >= 4.5 and move == 1) or (paddle_x <= -4.5 and move == -1):
                    genome.fitness -= 0.1  
            else:
                if ball_data["vy"] > 0 and current_distance > 0.5:
                    genome.fitness -= 0.05
    
            previous_ball_x = ball_x  
    
        except Exception as e:
            print(f"⚠️ AI 오류: {e}")

    @sio.event
    def hitPaddle(data):
        nonlocal fitness, hit_count
        hit_count += 1

        paddle_x = data.get("paddle_x", 0.0)
        ball_x = data.get("ball_x", 0)
        distance = abs(ball_x - paddle_x)
        reward = max(1.0 - distance, 0)

        fitness += reward * 3.0  
        genome.fitness += reward * 3.0  
        genome.fitness += 15  

    @sio.event
    def gameOver(data):
        global generation
        nonlocal hit_count
        with open("ai_log.txt", "a") as log_file:
                log_file.write(f"🎮 게임 종료! 최종 피트니스: {genome.fitness:.0f} / 현재 세대: {generation}\n")

        if genome.fitness < 0 and hit_count > 0:
            genome.fitness = max(hit_count * 0.5, 1)  
        
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
        print(f"AI 서버 연결 실패: {e}")

def train_ai(genomes, config):
    global generation

    for genome_id, genome in genomes:
        genome.fitness = random.uniform(0.1, 1.0)

    for genome_id, genome in genomes:
        run_ai_instance(genome, config, genome_id)
    generation += 1

def run_neat():
    config_path = "config-feedforward"
    config = neat.Config(
        neat.DefaultGenome,
        neat.DefaultReproduction,
        neat.DefaultSpeciesSet,
        neat.DefaultStagnation,
        config_path,
    )

    population = neat.Population(config)
    population.add_reporter(neat.StdOutReporter(True))
    stats = neat.StatisticsReporter()
    population.add_reporter(stats)

    winner = population.run(train_ai, 50)

    with open("best_ai.pkl", "wb") as f:
        pickle.dump(winner, f)

    print(" 저장 완료! ")

if __name__ == "__main__":
    run_neat()
