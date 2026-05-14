FROM debian:bookworm

RUN apt update && apt upgrade -y && apt install -y nginx openssl

RUN mkdir -p /etc/nginx/sites-available/

# Copia a config direto para o local onde o Nginx a lê
COPY conf/nginx.conf /etc/nginx/sites-available/default

# Cria o diretório para os certificados
RUN mkdir -p /etc/nginx/ssl

# Gera o certificado com caminhos fixos
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/nginx/ssl/cert.key -out /etc/nginx/ssl/cert.crt -subj "/C=PT/ST=Porto/L=Porto/O=42/OU=resilva/CN=resilva.42.fr"

# O Nginx no Debian precisa de um link simbólico para "ativar" o site, 
# mas o 'default' geralmente já vem linkado. Por segurança:
RUN ln -sf /etc/nginx/sites-available/default /etc/nginx/sites-enabled/default

ENTRYPOINT ["nginx", "-g", "daemon off;"]