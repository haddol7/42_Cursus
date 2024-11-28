all: up

up:
	sudo mkdir -p /home/daeha/data/db /home/daeha/data/wp
	docker-compose -f srcs/docker-compose.yml up --build -d

down:
	docker-compose -f srcs/docker-compose.yml down

clean: down
	sudo rm -rf /home/daeha/data/db /home/daeha/data/wp
	docker system prune -af
	docker volume prune -f

ps:
	@docker-compose -f srcs/docker-compose.yml ps
	@echo "\n"
	@docker images
	@echo "\n"
	@docker volume ls

logs:
	@docker logs mariadb
	@echo "\n"
	@docker logs wordpress
	@echo "\n"
	@docker logs nginx

re: clean all
