# Services provided

There are a total of 3 containers, each containing a different service:

- A *wordpress* container with *php-fpm*
- Nginx an high-performance web server, reverse proxy, load balancer, and HTTP cache
- MariaDB a relational database management system designed as a high-performance, drop-in replacement for MySQL

# Starting up the project

First you need to check the [credentials](#locate-and-manage-credentials) part of this documentation.

Inside the makefile provided there's a bunch of different rules to run and debug this project, running `make` will build the project and create the folders inside your $HOME directory, after this you can run `make up` this will start up the containers
`make down` will allow you to stop the containers, edit files and run them again with `make up`.
If everything goes wrong running `make fclean` will delete everything related to the containers and will allow you to run `make` again to build everything from the ground up.

# Accessing the admin page

To access the admin page you'll need to start up the compose with `make`, after it just go to your prefered browser of choice and search `resilva.42.fr/wp-admin/index.php` and this will take you directly to the wordpress admin page

# Locate and manage credentials

There's no .env file in this repository since it contains passwords, you'll need to create one, open up the `srcs/` folder and create a .env file with the following variables:

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

You just need to set the variables that don't have a value after the `=` sign, just like the `DOMAIN_NAME` is set

# Checking if everything is running smoothly

There's a few ways to check if everything is running as it should.

First `docker ps` will show the containers that are running and `docker logs $(container name)` will show you the logs of the specified container.

With the first command, after you started the compose, it should appear the 3 containers alongside with their status, if any of the containers is showing "restarting" something went wrong, if that's the case or if anything isn't working as it 
should, use `docker logs` to more quickly find what went wrong.
