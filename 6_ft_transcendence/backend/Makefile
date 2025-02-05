all:
	docker compose up -d db \
	&& docker compose up -d --build auth jwt twofa game websocket nginx \
	&& docker compose logs -f

clean:
	docker compose down -t 1

fclean:
	docker compose down -v -t 1 --rmi