FROM debian:bookworm

# Install PHP-FPM, MySQLi extension for database connection, and curl for WP-CLI
RUN apt update && apt upgrade -y && apt install -y \
php8.2-fpm \
php8.2-mysqli \
curl

# Create the PID directory for PHP-FPM and set permissions for the web user
RUN mkdir -p /run/php && chown -R www-data:www-data /run/php

# Copy PHP-FPM pool configuration and the installation script
COPY conf/www.conf /etc/php/8.2/fpm/pool.d/.
COPY ./tools/wp-install.sh .

# Expose port 9000 for FastCGI communication with Nginx
EXPOSE 9000

# Make the installation script executable
RUN chmod +x wp-install.sh

# Set the entrypoint to the setup script
ENTRYPOINT ["./wp-install.sh"]