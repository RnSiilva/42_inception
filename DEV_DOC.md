# How to setup the environment from scratch.

After creating your own VM with a linux based distribution, this is not obligatory but i never tested the project outside of this environment, you'll need to change just one tiny thing on the `/etc/hosts` file.

`127.0.0.1  localhost` -> `127.0.0.1  resilva.42.fr`

After this you can clone this repository and for the env variables you'll need to set this ones:

```
DOMAIN_NAME=resilva.42.fr

DB_NAME=
DB_USER=
DB_PASSWORD=
DB_HOST=

WORDPRESS_TITLE=
WORDPRESS_ADMIN_USER=
WORDPRESS_ADMIN_PASSWORD=
WORDPRESS_ADMIN_EMAIL=
WORDPRESS_USER=
WORDPRESS_PASSWORD=
WORDPRESS_EMAIL=
WP_GUEST_USER=
WP_GUEST_PASSWORD=
WP_GUEST_EMAIL=
```

Only the domain name needs to stay, everything else can be set to your liking

# Building the project

Running `make` on the root of this repository will build the stack using the `docker-compose.yml` file present on the `./srcs/` folder

# Debugging

If anything goes wrong there are some easy commands that one can run, namely:

`docker logs ${container name}` -> let's you see the logs of the container 

`docker exec -it ${container name} /bin/sh` -> let's you into the bash of the respective container

`docker volumes ls` -> let's you check the volumes 

# Data

The volumes and files of the containers are stored inside your $HOME/Inception_data folder, after building these locations will be restricted and can only be deleted through a priviliged user
