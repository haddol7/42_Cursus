all:
	docker compose up -d --build backend jwt db test-container auth websocket \
	&& docker compose logs -f
