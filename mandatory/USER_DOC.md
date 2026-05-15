# USER Documentation

## Services Provided

This project is composed of 3 Docker containers:

- **Nginx**  
  High-performance web server used as a reverse proxy and HTTPS server.

- **WordPress + PHP-FPM**  
  Runs the WordPress application using PHP-FPM.

- **MariaDB**  
  Relational database used by WordPress.

---

## Domain Configuration

Before starting the project, you must add the following line to your `/etc/hosts` file:

```text
127.0.0.1 resilva.42.fr
```

This allows your machine to resolve `resilva.42.fr` locally and access the website correctly.

You can add it with:

```bash
echo "127.0.0.1 resilva.42.fr" | sudo tee -a /etc/hosts
```

---

## Starting the Project

Before starting the project, make sure the required environment variables and secrets are configured.  
See the [Credentials](#credentials) section below.

### Build and start the project

```bash
make
```

This command:
- Builds the Docker images
- Creates the required directories inside `$HOME/data`
- Starts all containers

---

### Start containers again

If the containers were previously stopped, they can be started again with:

```bash
make up
```

---

### Stop containers

```bash
make stop
```

Stops the containers without removing them.

---

### Remove containers

```bash
make down
```

Stops and removes containers and networks.

---

### Remove everything and rebuild from scratch

```bash
make fclean
```

This command removes:
- Containers
- Images
- Volumes
- Networks
- Persistent data

---

## Accessing the Website

Once the containers are running, open your browser and access:

```text
https://resilva.42.fr
```

### WordPress Administration Panel

```text
https://resilva.42.fr/wp-admin
```

---

## Credentials

### Environment Variables

Create a `.env` file inside the `srcs/` directory:

```env
WP_DOMAIN=resilva.42.fr

DB_NAME=
DB_USER=
DB_HOST=

WP_TITLE=
WP_ADMIN_USER=
WP_ADMIN_EMAIL=

WP_GUEST_USER=
WP_GUEST_EMAIL=
```

---

### Docker Secrets

Create a `secrets/` directory at the root of the repository:

```text
secrets/
```

Inside this folder, create the following files:

```text
db_password.txt
db_root_password.txt
credentials.txt
```

Each file must contain only its corresponding password value.

Example:

```text
db_password.txt -> database user password
db_root_password.txt -> MariaDB root password
credentials.txt -> WordPress admin password
```

---

## Checking Service Status

### List running containers

```bash
make status
```

All 3 containers should appear with the status `Up`.

---

### View container logs

```bash
docker logs <container_name>
```

If a container is constantly restarting, use the logs to identify the issue.

---

## Persistent Data

Project data is stored inside:

```text
$HOME/data
```

This allows the database and WordPress files to persist even after containers are stopped.