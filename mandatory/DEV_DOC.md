# Developer Documentation

## Prerequisites

Required tools:

- Docker
- Docker Compose
- GNU Make

For the 42 project, this infrastructure must run inside a Linux virtual machine.

---

## Domain Configuration

Add the following line to `/etc/hosts`:

```text
127.0.0.1 resilva.42.fr
```

This allows the domain to resolve locally and correctly redirect traffic to the Nginx container.

You can add it with:

```bash
echo "127.0.0.1 resilva.42.fr" | sudo tee -a /etc/hosts
```

---

## Environment Setup

Clone the repository and create the required configuration files.

### Environment Variables

Create the following file:

```text
srcs/.env
```

Content:

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

Only `WP_DOMAIN` should remain unchanged.

---

## Docker Secrets

Create a directory named:

```text
secrets/
```

Inside it, create the following files:

```text
db_password.txt
db_root_password.txt
credentials.txt
```

Each file must contain only its corresponding secret value.

Example:

```text
db_password.txt -> database user password
db_root_password.txt -> MariaDB root password
credentials.txt -> WordPress admin password
```

---

## Building and Launching

### Build and start the project

```bash
make
```

This command:
- Builds all Docker images
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

### Full cleanup

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

## Useful Docker Commands

### List running containers

```bash
make status
```

---

### View container logs

```bash
docker logs <container_name>
```

---

### Access a container shell

```bash
docker exec -it <container_name> /bin/sh
```

---

### List Docker volumes

```bash
docker volume ls
```

---

## Data Persistence

Persistent project data is stored inside:

```text
$HOME/data
```

This includes:
- MariaDB database files
- WordPress website files

Because Docker volumes are mounted from the host machine, the data persists even if the containers are stopped or removed.