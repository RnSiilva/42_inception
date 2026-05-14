# Inception

*This project has been created as part of the 42 curriculum by resilva.*

## 📝 Description
**Inception** is a System Administration project that aims to broaden knowledge of infrastructure virtualization using **Docker**. The goal is to build a complete, resilient, and secure infrastructure composed of several services (NGINX, WordPress, and MariaDB) running in isolated containers. The orchestration is handled by Docker Compose, ensuring that each service is configured from scratch using customized Dockerfiles based on Debian Bookworm.

## 🏗️ Project Design & Technical Choices

This project follows a microservices architecture where each service has its own dedicated environment. Key design choices include:
- **Base Image:** All containers use **Debian Bookworm** to ensure stability and a lightweight footprint.
- **Security:** Services communicate through a private bridge network, and sensitive data is handled via Docker Secrets rather than plain environment variables.
- **Persistence:** System data is stored in host-mapped volumes to ensure database and website content survive container restarts.

### Technical Comparisons

#### 1. Virtual Machines vs Docker
- **Virtual Machines (VMs):** VMs virtualize the hardware. Each instance includes a full Operating System, its own Kernel, and drivers. This results in high resource consumption (RAM/CPU) and slow boot times.
- **Docker:** Containers virtualize the Operating System. They share the Host's Kernel and use **Namespaces** (for isolation) and **Control Groups** (for resource limiting). This makes them extremely lightweight, fast, and portable.

#### 2. Secrets vs Environment Variables
- **Environment Variables:** These are stored in plain text and can be easily exposed through `docker inspect`, system logs, or by running `env` inside the container.
- **Secrets:** Used in this project for DB and Admin passwords. Secrets are mounted into a temporary memory-based filesystem (**tmpfs**) at `/run/secrets/`. They never touch the container's writable layer or the disk, providing a much higher level of security.

#### 3. Docker Network vs Host Network
- **Host Network:** The container shares the host's IP and port space. There is no isolation, leading to potential port conflicts and security risks.
- **Docker Network (Bridge):** We use a custom bridge network called `inception`. This provides an isolated virtual network where containers can communicate using service names (DNS), but remain invisible to the external network unless explicitly mapped.

#### 4. Docker Volumes vs Bind Mounts
- **Bind Mounts:** These link a specific path on the host machine to the container. We use them here to fulfill the requirement of storing data in `/home/resilva/data`.
- **Docker Volumes:** These are managed by the Docker engine. While we use a "Bind" driver for this project, the Volume abstraction allows Docker to manage the lifecycle and permissions of the data more effectively than a raw mount.

## 🛠️ Instructions

### Prerequisites
- Docker and Docker Compose installed.
- Sudo privileges.
- Add the domain to your `/etc/hosts` file:
  ```bash
  echo "127.0.0.1 resilva.42.fr" | sudo tee -a /etc/hosts 
  ```

### Execution
To build and start the entire infrastructure:
```bash
git clone [...]
make
```

### Main Commands
Command Description
make build
Builds the Docker images for all services.
make up Starts the containers in detached mode.
make stop Stops the running containers.
make clean Removes containers, networks, and the data folder.
make fclean Full cleanup: removes images, volumes, and Docker cache.
make re Performs a full fclean followed by a new build.📚 

## Resources
### References
Official Docker DocumentationNGINX Configuration GuideWordPress CLI HandbookMariaDB Knowledge Base

### AI UsageAI
(Gemini 3 Flash) was utilized in this project for the following tasks:
- Makefile Optimization: Assisting with dependency logic to ensure idempotency between up and mkdirs rules.
- Shell Scripting: Designing the synchronization logic in wp-install.sh to ensure WordPress waits for MariaDB connectivity.
- Documentation: Refining the technical comparisons (VMs vs Docker, etc.) to ensure they meet the specific academic requirements of the 42 subject.
- Debugging: Analyzing container logs to troubleshoot volume permission issues and NGINX configuration errors.