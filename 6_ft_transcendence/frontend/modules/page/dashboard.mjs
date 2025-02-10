import { renderNavBar, bindEventToNavBar } from "./lowRankElements.mjs";
import { PageManager } from "./manager.mjs";






export class DashBoardPage {
	static async fetchData() {
		try {
			const response = await fetch("https://api.example.com/game-stats"); // Replace with actual API URL
			const data = await response.json();
			return data;
		} catch (error) {
			console.error("Failed to fetch data", error);
			return null;
		}
	}
	static async render() {
		renderNavBar();

		document.body.innerHTML += `
      <div id="dashBoardSection" style="border: 1px solid gray; margin: 4px; padding: 16px; background: #f4f4f4;">
        <h2>Dashboard</h2>
        <div class="dashboard-container" style="display: flex; gap: 16px;">
          <!-- User Stats Section -->
          <div class="user-stats" style="flex: 1; background: white; padding: 16px; border-radius: 8px; box-shadow: 0 0 10px rgba(0,0,0,0.1);">
            <h3>User Statistics</h3>
            <p id=totalGames>Total Games Played: 120</p>
            <div id="userChart"> 
			<canvas id="doughnut-chart" width="400" height="200"></canvas>
			<p>Win/Loss Ratio: 65%</p>
			<canvas id="line-chart" width="400" height="150"></canvas>
			<canvas id="bar-chart-horizontal" width="400" height="150"></canvas>
			</div>
			<div id="userLogs">
			<div class="accordion" id="accordionExample">
  <div class="accordion-item">
    <h2 class="accordion-header">
      <button class="accordion-button" type="button" data-bs-toggle="collapse" data-bs-target="#collapseOne" aria-expanded="true" aria-controls="collapseOne">
        Accordion Item #1
      </button>
    </h2>
    <div id="collapseOne" class="accordion-collapse collapse show" data-bs-parent="#accordionExample">
      <div class="accordion-body">
        <strong>This is the first item's accordion body.</strong> It is shown by default, until the collapse plugin adds the appropriate classes that we use to style each element. These classes control the overall appearance, as well as the showing and hiding via CSS transitions. You can modify any of this with custom CSS or overriding our default variables. It's also worth noting that just about any HTML can go within the <code>.accordion-body</code>, though the transition does limit overflow.
      </div>
    </div>
  </div>
  <div class="accordion-item">
    <h2 class="accordion-header">
      <button class="accordion-button collapsed" type="button" data-bs-toggle="collapse" data-bs-target="#collapseTwo" aria-expanded="false" aria-controls="collapseTwo">
        Accordion Item #2
      </button>
    </h2>
    <div id="collapseTwo" class="accordion-collapse collapse" data-bs-parent="#accordionExample">
      <div class="accordion-body">
        <strong>This is the second item's accordion body.</strong> It is hidden by default, until the collapse plugin adds the appropriate classes that we use to style each element. These classes control the overall appearance, as well as the showing and hiding via CSS transitions. You can modify any of this with custom CSS or overriding our default variables. It's also worth noting that just about any HTML can go within the <code>.accordion-body</code>, though the transition does limit overflow.
      </div>
    </div>
  </div>
  <div class="accordion-item">
    <h2 class="accordion-header">
      <button class="accordion-button collapsed" type="button" data-bs-toggle="collapse" data-bs-target="#collapseThree" aria-expanded="false" aria-controls="collapseThree">
        Accordion Item #3
      </button>
    </h2>
    <div id="collapseThree" class="accordion-collapse collapse" data-bs-parent="#accordionExample">
      <div class="accordion-body">
        <strong>This is the third item's accordion body.</strong> It is hidden by default, until the collapse plugin adds the appropriate classes that we use to style each element. These classes control the overall appearance, as well as the showing and hiding via CSS transitions. You can modify any of this with custom CSS or overriding our default variables. It's also worth noting that just about any HTML can go within the <code>.accordion-body</code>, though the transition does limit overflow.
      </div>
    </div>
  </div>
</div>
			</div>
          </div>

          <!-- Game Session Stats Section -->
          <div class="game-session-stats" style="flex: 1; background: white; padding: 16px; border-radius: 8px; box-shadow: 0 0 10px rgba(0,0,0,0.1);">
            <h3>Game Session Stats</h3>
            <p>Recent Matches: 5</p>
            <p>five top winner</p>
            <div id="gameChart">
			<canvas id="polar-chart" width="400" height="250"></canvas>
			<canvas id="bar-chart" width="400" height="250"></canvas>
			</div>
			<div id="gameLog">
			<div class="accordion" id="accordionExample">
  <div class="accordion-item">
    <h2 class="accordion-header">
      <button class="accordion-button" type="button" data-bs-toggle="collapse" data-bs-target="#collapseOne" aria-expanded="true" aria-controls="collapseOne">
        Accordion Item #1
      </button>
    </h2>
    <div id="collapseOne" class="accordion-collapse collapse show" data-bs-parent="#accordionExample">
      <div class="accordion-body">
        <strong>This is the first item's accordion body.</strong> It is shown by default, until the collapse plugin adds the appropriate classes that we use to style each element. These classes control the overall appearance, as well as the showing and hiding via CSS transitions. You can modify any of this with custom CSS or overriding our default variables. It's also worth noting that just about any HTML can go within the <code>.accordion-body</code>, though the transition does limit overflow.
      </div>
    </div>
  </div>
  <div class="accordion-item">
    <h2 class="accordion-header">
      <button class="accordion-button collapsed" type="button" data-bs-toggle="collapse" data-bs-target="#collapseTwo" aria-expanded="false" aria-controls="collapseTwo">
        Accordion Item #2
      </button>
    </h2>
    <div id="collapseTwo" class="accordion-collapse collapse" data-bs-parent="#accordionExample">
      <div class="accordion-body">
        <strong>This is the second item's accordion body.</strong> It is hidden by default, until the collapse plugin adds the appropriate classes that we use to style each element. These classes control the overall appearance, as well as the showing and hiding via CSS transitions. You can modify any of this with custom CSS or overriding our default variables. It's also worth noting that just about any HTML can go within the <code>.accordion-body</code>, though the transition does limit overflow.
      </div>
    </div>
  </div>
  <div class="accordion-item">
    <h2 class="accordion-header">
      <button class="accordion-button collapsed" type="button" data-bs-toggle="collapse" data-bs-target="#collapseThree" aria-expanded="false" aria-controls="collapseThree">
        Accordion Item #3
      </button>
    </h2>
    <div id="collapseThree" class="accordion-collapse collapse" data-bs-parent="#accordionExample">
      <div class="accordion-body">
        <strong>This is the third item's accordion body.</strong> It is hidden by default, until the collapse plugin adds the appropriate classes that we use to style each element. These classes control the overall appearance, as well as the showing and hiding via CSS transitions. You can modify any of this with custom CSS or overriding our default variables. It's also worth noting that just about any HTML can go within the <code>.accordion-body</code>, though the transition does limit overflow.
      </div>
    </div>
  </div>
</div>
			</div>
          </div>
        </div>
      </div>
    `;

		bindEventToNavBar();
		PageManager.currentpageStatus = PageManager.pageStatus.dashBoard;

		// Fetch and update stats
		const stats = await DashBoardPage.fetchData();
		if (stats) {
			document.getElementById("totalGames").textContent = `Total Games Played: ${stats.totalGames}`;
			document.getElementById("winLossRatio").textContent = `Win/Loss Ratio: ${stats.winLossRatio}%`;
			document.getElementById("highestScore").textContent = `Highest Score: ${stats.highestScore}`;
			document.getElementById("recentMatches").textContent = `Recent Matches: ${stats.recentMatches}`;
			document.getElementById("averageScore").textContent = `Average Score: ${stats.averageScore}`;
			document.getElementById("winLossDistribution").textContent = `Win/Loss Distribution: ${stats.winLossDistribution}`;
		}

		new Chart(document.getElementById("doughnut-chart"), {
			type: 'doughnut',
			data: {
				labels: ["win", "loss"],
				datasets: [
					{
						label: "Population (millions)",
						backgroundColor: ["#3e95cd", "#8e5ea2", "#3cba9f", "#e8c3b9", "#c45850"],
						data: [12, 7]
					}
				]
			},
			options: {
				title: {
					display: true,
					text: 'win rate'
				}
			}
		});

		new Chart(document.getElementById("line-chart"), {
			type: 'line',
			data: {
				labels: ["n-4 match", "n-3 match", "n-2 match", "n-1 match", "n match"],
				datasets: [{
					data: [0, 0, 0.50, 0.30, 0.7],
					label: "user a",
					borderColor: "#3e95cd",
					fill: false
				}, {
					data: [0.51, 0.515, 0.52, 0.525, 0.52],
					label: "average",
					borderColor: "#8e5ea2",
					fill: false
				}
				]
			},
			options: {
				title: {
					display: true,
					text: 'winRateChange'
				}
			}
		});

		new Chart(document.getElementById("polar-chart"), {
			type: 'polarArea',
			data: {
				labels: ["a", "b", "c", "d", "e"],
				datasets: [
					{
						label: "win ranking",
						backgroundColor: ["#3e95cd", "#8e5ea2", "#3cba9f", "#e8c3b9", "#c45850"],
						data: [12, 9, 8, 4, 3]
					}
				]
			},
			options: {
				title: {
					display: true,
					text: 'five top winner'
				}
			}
		});
		new Chart(document.getElementById("bar-chart-horizontal"), {
			type: 'horizontalBar',
			data: {
				labels: ["user a", "top ranker"],
				datasets: [
					{
						label: "play time",
						backgroundColor: ["#3e95cd", "#8e5ea2", "#3cba9f", "#e8c3b9", "#c45850"],
						data: [120, 200, 50]
					}
				]
			},
			options: {
				legend: { display: false },
				title: {
					display: true,
					text: 'play time'
				}
			}
		});
		new Chart(document.getElementById("bar-chart"), {
			type: 'bar',
			data: {
				labels: ["a", "b", "c", "d", "e"],
				datasets: [
					{
						label: "game time",
						backgroundColor: ["#3e95cd", "#8e5ea2", "#3cba9f", "#e8c3b9", "#c45850"],
						data: [2478, 5267, 734, 784, 433]
					}
				]
			},
			options: {
				legend: { display: false },
				title: {
					display: true,
					text: 'game time'
				}
			}
		});
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


