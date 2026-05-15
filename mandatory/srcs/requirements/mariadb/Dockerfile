FROM debian:bookworm

# Update system and install MariaDB server
RUN apt update && apt upgrade -y && apt install -y mariadb-server

# Copy custom configuration and the entrypoint script
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/.
COPY tools/mariadb-run.sh .

# Document the standard MariaDB port
EXPOSE 3306

# Create required runtime directory and make the script executable
RUN mkdir /run/mysqld && chmod +x ./mariadb-run.sh

# Execute the startup script when the container launches
ENTRYPOINT ["./mariadb-run.sh"]