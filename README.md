*This project has been created as part of the 42 curriculum by resilva.*

---

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
- **Host Network:** The container shares the host's networking namespace directly. It uses the host's IP address and ports with no isolation, meaning if two containers try to use port 80, a conflict occurs.
- **Docker Network (Bridge):** It creates a private, isolated virtual network for your containers. Inside this network, containers can talk to each other safely using their service names (like a private phone book), while keeping backend services (like MariaDB) completely hidden and inaccessible from the outside world.

#### 4. Docker Volumes vs Bind Mounts
- **Docker Volumes:** Are stored and managed entirely by Docker in an isolated area of ​​the filesystem, ensuring better portability and data security. Used here to persist MariaDB and WordPress data in `/home/resilva/data`. Docker controls lifecycle and permissions.
- **Bind Mounts:** Link a container directly to a specific directory on the local computer, allowing immediate access and modification of files from the host system.

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
git clone git@github.com:RnSiilva/42_inception.git $HOME/Inception
cd $HOME/Inception
make
```

## Resources
### References
- [How to install docker engine](https://docs.docker.com/engine/install/debian/)
- [Docker networking explained](https://bhavyansh001.medium.com/docker-networking-explained-after-3-days-of-pulling-my-hair-out-7b91fa623802)
- [Nginx documentation](https://docs.nginx.com/)
- [MariaDB documentation](https://mariadb.com/docs)
- [The Docker Docs](https://docs.docker.com/)


### AI Usage
Artificial Intelligence tools were used as a support resource throughout the development of this project. They were mainly used for learning and better understanding key concepts, helping with project organization, and assisting in debugging and troubleshooting issues during implementation. All final decisions and code were developed and validated manually.