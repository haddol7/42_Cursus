all:
	docker compose up -d --build db auth jwt twofa game websocket \
	&& docker compose logs -f
