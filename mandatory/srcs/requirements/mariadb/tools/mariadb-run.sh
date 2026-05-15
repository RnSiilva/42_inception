#!/bin/bash

# 1. Load database passwords from Docker secrets
DB_PASSWORD=$(cat /run/secrets/db_password)
DB_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)

# 2. Create the SQL setup file dynamically using environment variables
echo "CREATE DATABASE IF NOT EXISTS \`${DB_NAME}\`;" > /etc/mysql/init.sql
echo "CREATE USER IF NOT EXISTS '$DB_USER'@'%' IDENTIFIED BY '$DB_PASSWORD';" >> /etc/mysql/init.sql
echo "GRANT ALL PRIVILEGES ON *.* TO '$DB_USER'@'%' WITH GRANT OPTION;" >> /etc/mysql/init.sql
echo "ALTER USER 'root'@'localhost' IDENTIFIED BY '$DB_ROOT_PASSWORD';" >> /etc/mysql/init.sql
echo "FLUSH PRIVILEGES;" >> /etc/mysql/init.sql

# 3. Ensure necessary directories and files have the correct ownership
mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld /var/lib/mysql /etc/mysql/init.sql

# 4. Bootstrap the system tables only if the database is not yet initializedif [ ! -d "/var/lib/mysql/mysql" ]; then
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "[MariaDB] Initializing system tables..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi

echo "[MariaDB] Iniciando o servidor..."

# 5. Launch the daemon as 'mysql' user, executing the init.sql file at startupexec mysqld --user=mysql --init-file=/etc/mysql/init.sql
exec mysqld --user=mysql --init-file=/etc/mysql/init.sql
