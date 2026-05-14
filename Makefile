# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/06 13:50:56 by resilva           #+#    #+#              #
#    Updated: 2026/05/14 01:00:55 by resilva          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: build up

mkdirs:
	mkdir -p ${HOME}/data/mariadb
	mkdir -p ${HOME}/data/wordpress

build: mkdirs
	docker-compose -f srcs/docker-compose.yml build

up: mkdirs
	docker compose -f srcs/docker-compose.yml up -d

status:
	docker ps

stop:
	docker compose -f srcs/docker-compose.yml stop

down:
	docker compose -f srcs/docker-compose.yml down

clean:
	docker compose -f srcs/docker-compose.yml down -v
	@sudo rm -rf ${HOME}/data

fclean:
	docker compose -f srcs/docker-compose.yml down --rmi all -v
	@sudo rm -rf ${HOME}/data
	docker system prune -af

re: fclean all

.PHONY: all mkdirs build up status stop down clean fclean re