#!/bin/bash

DB_PASSWORD=$(cat /run/secrets/db_password)
WP_PASSWORD=$(cat /run/secrets/wp_admin_password)

cd /var/www/html

# 1. Check if WP-CLI already exists; if not, download it
if [ ! -f wp-cli.phar ]; then
	curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
	chmod +x wp-cli.phar
fi

# 2. It will only install if wp-config.php does NOT exist.
if [ ! -f wp-config.php ]; then
	echo "Starting WordPress installation..."
	# Waiting for MariaDB (Important!)
	sleep 5
	./wp-cli.phar core download --allow-root

	./wp-cli.phar config create --dbname=${DB_NAME} --dbuser=${DB_USER} --dbpass=${DB_PASSWORD} --dbhost=${DB_HOST} --allow-root

	./wp-cli.phar core install --url=${WP_DOMAIN} --title=${WP_TITLE} --admin_user=${WP_ADMIN_USER} --admin_password=${WP_PASSWORD} --admin_email=${WP_ADMIN_EMAIL} --allow-root

	./wp-cli.phar user create ${WP_GUEST_USER} ${WP_GUEST_EMAIL} --role=subscriber --user_pass=${WP_PASSWORD} --allow-root

	echo "WordPress installed successfully!"
else
	echo "WordPress is already configured, so installation is skipped."
fi

# Inicia o serviço
exec php-fpm8.2 -F