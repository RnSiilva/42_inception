all: build up

mkdirs:
	mkdir -p ${HOME}/data/mariadb
	mkdir -p ${HOME}/data/wordpress

build: mkdirs
	docker compose -f srcs/docker-compose.yml build

up: mkdirs
	docker compose -f srcs/docker-compose.yml up -d

status:
	docker ps

stop:
	docker compose -f srcs/docker-compose.yml stop

down:
	docker compose -f srcs/docker-compose.yml down

clean: down

fclean:
	docker compose -f srcs/docker-compose.yml down --rmi all -v
	@sudo rm -rf ${HOME}/data
	docker system prune -af

re: fclean all

.PHONY: all mkdirs build up status stop down clean fclean re