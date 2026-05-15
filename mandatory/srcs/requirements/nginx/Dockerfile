FROM debian:bookworm

# Install Nginx for the web server and OpenSSL for TLS/SSL certificates
RUN apt update && apt upgrade -y && apt install -y nginx openssl

# Ensure the configuration directory exists
RUN mkdir -p /etc/nginx/sites-available/

# Overwrite the default Nginx config with our custom configuration
COPY conf/nginx.conf /etc/nginx/sites-available/default

# Create a secure directory to store SSL certificates
RUN mkdir -p /etc/nginx/ssl

# Generate a self-signed SSL certificate (TLS v1.2/v1.3 requirement)
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/cert.key \
    -out /etc/nginx/ssl/cert.crt \
    -subj "/C=PT/ST=Porto/L=Porto/O=42/OU=resilva/CN=resilva.42.fr"

# Start Nginx in the foreground to keep the container running
ENTRYPOINT ["nginx", "-g", "daemon off;"]