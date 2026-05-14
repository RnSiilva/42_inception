# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/06 13:50:56 by resilva           #+#    #+#              #
#    Updated: 2026/05/12 22:39:00 by resilva          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: build run

data:
	@if [ ! -d "home/resilva/data/mariadb"] && [ ! -d "home/resilva/data/wordpress;" ]; then \
	mkdir -p home/resilva/data/mariadb && mkdir -p home/resilva/data/wordpress; fi

build: data
	docker-compose -f srcs/docker-compose.yml build

run:
	docker compose -f srcs/docker-compose.yml up -d

exec:
	$(eval service=$(filter-out $@,$(MAKECMDGOALS)))
	docker compose -f srcs/docker-compose.yml logs #(service)

stop:
	docker compose -f srcs/docker-compose.yml down

iclean:
	docker compose -f srcs/docker-compose.yml down --rmi all

vclean:
	docker compose -f srcs/docker-compose.yml down --rmi all -v
	@sudo rm -rf home

fclean: vclean
	docker system prune -af

dls:
	docker ps -a

vls:
	docker volume ls

ils:
	docker image ls

nls:
	docker networks ls

.SILENT: