import { renderNavBar, bindEventToNavBar } from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";
import { JWT } from "../authentication/jwt.mjs";
import { WHEN_EXPIRED } from "../authentication/globalConstants.mjs";
import { activateScrollBar } from "./utility.mjs";

/////////////////////////
// 예시 데이터: 최근 5경기 점수 정보
// const testJson = {
// 	"user_session": {
// 		"user_stats": { //유저 섹터, 일반적으로 표현할 데이터
// 			"user_name": "choolee", //유저 이름
// 			"total_games": 50 //유저의 총 게임 횟수
// 		},
// 		"user_win_rate": { //유저 섹터, 도넛 그래프, 유저 현재 승률을 표현할 데이터
// 			"wins": 30, //유저의 이긴 횟수
// 			"losses": 20 //유저의 진 횟수
// 		},
// 		"win_rate_trend": { //유저 섹터, 라인 그래프, 유저 승률 변화량을 나타낼 데이터,1등 유저 승률 변화량과 비교 (최대 5개)
// 			"current_user": [0.6, 0.58, 0.57, 0.55, 0.53], //n-4게임 승률, n-3게임 승률, n-2게임 승률, n-1게임 승률, n게임 승률, 5번의 경기가 안 되었을 경우 0으로 채움
// 			"top_user": [0.75, 0.74, 0.73, 0.72, 0.71] // 1등 유저 케이스
// 		},
// 		"total_game_time": { //유저 섹터, 수평 바 그래프, 총 게임 시간과 해당 유저의 총 게임 시간
// 			"user_total_time": 14.8, //해당 유저의 총 게임 시간
// 			"avg_total_time": 15.2 //모든 유저의 총 게임 시간의 평균
// 		},
// 		"recent_user_matches": [ //유저 섹터, 아코디언, 들어갈 데이터 (최대 10개, 최근 것 기준으로)
// 			{
// 				"user_name": "choolee", //유저 이름
// 				"opponent_name": "Bob", //상대방 이름
// 				"win": true, //이겼는지 졌는지, 이기면 1, 지면 0
// 				"user_score": 11, //유저 스코어
// 				"opponent_score": 9, //상대방 스코어
// 				"game_time": 240 //해당 게임 시간
// 			},
// 			{
// 				"user_name": "choolee",
// 				"opponent_name": "Charlie",
// 				"win": false,
// 				"user_score": 8,
// 				"opponent_score": 11,
// 				"game_time": 240
// 			},
// 			{
// 				"user_name": "choolee",
// 				"opponent_name": "Charlie",
// 				"win": false,
// 				"user_score": 8,
// 				"opponent_score": 11,
// 				"game_time": 240
// 			},
// 			{
// 				"user_name": "choolee",
// 				"opponent_name": "Charlie",
// 				"win": false,
// 				"user_score": 8,
// 				"opponent_score": 11,
// 				"game_time": 240.3
// 			}
// 		],
// 	},
// 	"game_session": {
// 		"top_5_winners": [ //게임 섹터, 폴라 그래프, 상위 5명의 승리 횟수
// 			{
// 				"user_name": "Charlie", //1등 유저의 이름
// 				"win_count": 45 //1등 유저의 승리 횟수
// 			},
// 			{
// 				"user_name": "Alice", //2등 유저의 이름
// 				"win_count": 30 //2등 유저의 승리 횟수
// 			},
// 			{
// 				"user_name": "Bob",
// 				"win_count": 25
// 			},
// 			{
// 				"user_name": "David",
// 				"win_count": 20
// 			},
// 			{
// 				"user_name": "Eve",
// 				"win_count": 15
// 			}
// 		],
// 		"top_5_game_time": [ //게임 섹터, 바 그래프, 상위 5명의 총 게임 시간
// 			{
// 				"user_name": "Charlie", //1등 유저
// 				"game_time": 16.5 //1등 유저의 총 게임 시간
// 			},
// 			{
// 				"user_name": "Alice",
// 				"game_time": 15.0
// 			},
// 			{
// 				"user_name": "Bob",
// 				"game_time": 14.3
// 			},
// 			{
// 				"user_name": "David",
// 				"game_time": 13.8
// 			},
// 			{
// 				"user_name": "Eve",
// 				"game_time": 13.5
// 			}
// 		],
// 		"recent_matches": [ //게임 섹터, 아코디언, 들어갈 데이터 (최대 10개, 최근 것 기준으로)
// 			{
// 				"winner_name": "David", //이긴 유저 이름
// 				"loser_name": "Eve", //진 유저 이름
// 				"winner_score": 5, //이긴 유저 스코어
// 				"loser_score": 2, //진 유저 스코어
// 				"match_playtime": 240 //해당 게임 시간
// 			},
// 			{
// 				"winner_name": "Frank",
// 				"loser_name": "Grace",
// 				"winner_score": 5,
// 				"loser_score": 2,
// 				"match_playtime": 240
// 			}
// 		],
// 	}
// };

///////////////////////////

export class DashBoardPage {
  static async fetchData() {
    const response = await fetch(
      "/api/user/dashboard",
      JWT.getOptionWithAccessToken("GET")
    ); // Replace with actual API URL
    const data = await response.json();

    // console.log(data);
    if (response.ok) return data;
    else {
      if (response.status === 401 && json.error === WHEN_EXPIRED) {
        try {
          await JWT.getNewToken();
          await this.fetchData();
        } catch (e) {
          alert(e);
        }
      } else alert(json.error);
    }
  }

  // 2. JSON 배열을 바탕으로 부트스트랩 아코디언을 동적으로 생성하는 메서드
  static renderAccordion(accordionItems, containerId) {
    // 아코디언 컨테이너 생성
    const accordionContainer = document.createElement("div");
    accordionContainer.className = "accordion";
    accordionContainer.id = containerId;

    // 각 항목별로 아코디언 아이템 생성
    accordionItems.forEach((item, index) => {
      // 유니크한 id 생성
      const itemId = `${containerId}-item-${index}`;

      // 아코디언 아이템 div
      const accordionItem = document.createElement("div");
      accordionItem.className = "accordion-item";

      // 아코디언 헤더
      const header = document.createElement("h2");
      header.className = "accordion-header";
      header.id = `heading-${itemId}`;

      const button = document.createElement("button");
      // 첫번째 아이템은 기본으로 펼치고, 나머지는 collapsed 클래스 추가
      button.className = "accordion-button" + (index !== 0 ? " collapsed" : "");
      button.type = "button";
      button.setAttribute("data-bs-toggle", "collapse");
      button.setAttribute("data-bs-target", `#collapse-${itemId}`);
      button.setAttribute("aria-expanded", index === 0 ? "true" : "false");
      button.setAttribute("aria-controls", `collapse-${itemId}`);
      button.textContent = item.title;

      header.appendChild(button);
      accordionItem.appendChild(header);

      // 아코디언 Collapse 영역
      const collapseDiv = document.createElement("div");
      collapseDiv.id = `collapse-${itemId}`;
      // 첫번째 항목은 기본으로 열려있도록 "show" 클래스 추가
      collapseDiv.className =
        "accordion-collapse collapse" + (index === 0 ? " show" : "");
      collapseDiv.setAttribute("aria-labelledby", `heading-${itemId}`);
      collapseDiv.setAttribute("data-bs-parent", "#accordionExample");

      const bodyDiv = document.createElement("div");
      bodyDiv.className = "accordion-body";
      // item.content에 HTML이 포함될 수 있으므로 innerHTML 사용
      bodyDiv.innerHTML = item.content;

      collapseDiv.appendChild(bodyDiv);
      accordionItem.appendChild(collapseDiv);

      // 컨테이너에 아코디언 아이템 추가
      accordionContainer.appendChild(accordionItem);
    });

    return accordionContainer;
  }

  static async render() {
    renderNavBar();

    document.body.innerHTML += `
			<div id="dashBoardSection" style="border: 1px solid gray; margin: 4px; padding: 16px; background: #f4f4f4;">
				<h2>Dashboard</h2>
				<div class="dashboard-container" style="display: flex; gap: 16px;">
					<!-- User Stats Section -->
					<div class="user-stats"
						style="flex: 1; background: white; padding: 16px; border-radius: 8px; box-shadow: 0 0 10px rgba(0,0,0,0.1);">
						<h3>User Statistics</h3>
						<p id=totalGames>Total Games Played: 0</p>
						<div id="userChart">
							<canvas id="doughnut-chart" width="400" height="170"></canvas>
							<p id="winLossRatio">Win/Loss Ratio: %</p>
							<canvas id="line-chart" width="400" height="150"></canvas>
							<canvas id="bar-chart-horizontal" width="400" height="150"></canvas>
						</div>
						<div id="userLogs">
							<div class="accordion" id="accordionExample">
							</div>
						</div>
					</div>

					<!-- Game Session Stats Section -->
					<div class="game-session-stats"
						style="flex: 1; background: white; padding: 16px; border-radius: 8px; box-shadow: 0 0 10px rgba(0,0,0,0.1);">
						<h3>Game Session Stats</h3>
						<p>five top rankers</p>
						<div id="gameChart">
							<canvas id="polar-chart" width="400" height="250"></canvas>
							<canvas id="bar-chart" width="400" height="250"></canvas>
						</div>
						<div id="gameLogs">
							
						</div>
					</div>
				</div>
			</div>
		`;

    bindEventToNavBar();
    PageManager.currentpageStatus = PageManager.pageStatus.dashBoard;

    // Fetch and update stats
    const testJson = await DashBoardPage.fetchData();
    if (testJson) {
      document.getElementById(
        "totalGames"
      ).textContent = `Total Games Played: ${testJson.user_session.user_stats.total_games}`;
      document.getElementById("winLossRatio").textContent = `Win/Loss Ratio: ${
        (testJson.user_session.user_win_rate.wins /
          testJson.user_session.user_stats.total_games) *
        100
      }%`;
    }

    // recent_user_matches 배열을 아코디언 데이터로 변환
    const userAccordionData = testJson.user_session.recent_user_matches.map(
      (match) => {
        return {
          title: `${match.user_name} vs ${match.opponent_name} (${
            match.win ? "Won" : "Lost"
          })`,
          content: `
				<p><strong>User Score:</strong> ${match.user_score}</p>
				<p><strong>Opponent Score:</strong> ${match.opponent_score}</p>
				<p><strong>Game Time:</strong> ${match.game_time} seconds</p>
	  			`,
        };
      }
    );

    // game_matchs 배열을 아코디언 데이터로 변환
    const gameAccordionData = testJson.game_session.recent_matches.map(
      (match) => {
        return {
          title: `Winner ${match.winner_name} vs ${match.loser_name}`,
          content: `
				<p><strong>Winner Score:</strong> ${match.winner_score}</p>
				<p><strong>Loser Score:</strong> ${match.loser_score}</p>
				<p><strong>Game Time:</strong> ${match.match_playtime} seconds</p>
	  			`,
        };
      }
    );

    // user 아코디언 생성
    const userAccordionElement = DashBoardPage.renderAccordion(
      userAccordionData,
      "accordionUser"
    );
    const userLogDiv = document.getElementById("userLogs");
    userLogDiv.innerHTML = ""; // 기존의 static 내용 제거
    userLogDiv.appendChild(userAccordionElement);

    // game 아코디언 생성
    const gameAccordionElement = DashBoardPage.renderAccordion(
      gameAccordionData,
      "accordionGame"
    );
    const gameLogDiv = document.getElementById("gameLogs");
    gameLogDiv.innerHTML = ""; // 기존의 static 내용 제거
    gameLogDiv.appendChild(gameAccordionElement);

    new Chart(document.getElementById("doughnut-chart"), {
      type: "doughnut",
      data: {
        labels: ["win", "loss"],
        datasets: [
          {
            label: "Population (millions)",
            backgroundColor: [
              "#3e95cd",
              "#8e5ea2",
              "#3cba9f",
              "#e8c3b9",
              "#c45850",
            ],
            data: [
              testJson.user_session.user_win_rate.wins,
              testJson.user_session.user_win_rate.losses,
            ],
          },
        ],
      },
      options: {
        title: {
          display: true,
          text: "win rate",
        },
      },
    });

    new Chart(document.getElementById("line-chart"), {
      type: "line",
      data: {
        labels: ["n-4 match", "n-3 match", "n-2 match", "n-1 match", "n match"],
        datasets: [
          {
            data: testJson.user_session.win_rate_trend.current_user,
            label: testJson.user_session.user_stats.user_name,
            borderColor: "#3e95cd",
            fill: false,
          },
          {
            data: testJson.user_session.win_rate_trend.top_user,
            label: "top ranker",
            borderColor: "#8e5ea2",
            fill: false,
          },
        ],
      },
      options: {
        title: {
          display: true,
          text: "winRateChange",
        },
      },
    });

    new Chart(document.getElementById("bar-chart-horizontal"), {
      type: "horizontalBar",
      data: {
        labels: [testJson.user_session.user_stats.user_name, "top ranker"],
        datasets: [
          {
            label: "play time",
            backgroundColor: [
              "#3e95cd",
              "#8e5ea2",
              "#3cba9f",
              "#e8c3b9",
              "#c45850",
            ],
            data: [
              testJson.user_session.total_game_time.user_total_time,
              testJson.user_session.total_game_time.avg_total_time,
            ],
          },
        ],
      },
      options: {
        legend: { display: false },
        title: {
          display: true,
          text: "play time",
        },
        scales: {
          xAxes: [
            {
              ticks: {
                beginAtZero: true,
              },
            },
          ],
        },
      },
    });

    new Chart(document.getElementById("polar-chart"), {
      type: "polarArea",
      data: {
        labels: [
          testJson.game_session.top_5_winners[0].user_name,
          testJson.game_session.top_5_winners[1].user_name,
          testJson.game_session.top_5_winners[2].user_name,
          testJson.game_session.top_5_winners[3].user_name,
          testJson.game_session.top_5_winners[4].user_name,
        ],
        datasets: [
          {
            label: "win ranking",
            backgroundColor: [
              "#3e95cd",
              "#8e5ea2",
              "#3cba9f",
              "#e8c3b9",
              "#c45850",
            ],
            data: [
              testJson.game_session.top_5_winners[0].win_count,
              testJson.game_session.top_5_winners[1].win_count,
              testJson.game_session.top_5_winners[2].win_count,
              testJson.game_session.top_5_winners[3].win_count,
              testJson.game_session.top_5_winners[4].win_count,
            ],
          },
        ],
      },
      options: {
        title: {
          display: true,
          text: "five top winner",
        },
      },
    });
    new Chart(document.getElementById("bar-chart"), {
      type: "bar",
      data: {
        labels: [
          testJson.game_session.top_5_winners[0].user_name,
          testJson.game_session.top_5_winners[1].user_name,
          testJson.game_session.top_5_winners[2].user_name,
          testJson.game_session.top_5_winners[3].user_name,
          testJson.game_session.top_5_winners[4].user_name,
        ],
        datasets: [
          {
            label: "game time",
            backgroundColor: [
              "#3e95cd",
              "#8e5ea2",
              "#3cba9f",
              "#e8c3b9",
              "#c45850",
            ],
            data: [
              testJson.game_session.top_5_game_time[0].game_time,
              testJson.game_session.top_5_game_time[1].game_time,
              testJson.game_session.top_5_game_time[2].game_time,
              testJson.game_session.top_5_game_time[3].game_time,
              testJson.game_session.top_5_game_time[4].game_time,
            ],
          },
        ],
      },
      options: {
        legend: { display: false },
        title: {
          display: true,
          text: "game time",
        },
        scales: {
          yAxes: [
            {
              ticks: {
                // beginAtZero: true
                suggestedMin:
                  testJson.game_session.top_5_game_time[4].game_time / 2,
              },
            },
          ],
        },
      },
    });
    activateScrollBar();
  }

  static renderAndPushHistory() {
    DashBoardPage.render();
    history.pushState(PageManager.pageStatus.dashBoard, "");
  }

  static destroy() {
    const dashBoardSection = document.getElementById("dashBoardSection");
    dashBoardSection.innerHTML = "";
    dashBoardSection.parentNode.removeChild(dashBoardSection);
  }
}
