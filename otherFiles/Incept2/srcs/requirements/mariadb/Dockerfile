FROM debian:bookworm

RUN apt update && apt upgrade -y && apt install -y mariadb-server

COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/.
COPY tools/mariadb-run.sh .

RUN mkdir /run/mysqld && chmod +x ./mariadb-run.sh

ENTRYPOINT ["./mariadb-run.sh"]