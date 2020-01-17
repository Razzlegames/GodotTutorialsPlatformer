FROM alpine:3.7
LABEL author="razzlegames@gmail.com"

RUN apk add --no-cache \
    ca-certificates \
    git \
    python \
    py3-openssl \ 
    unzip \
    wget \
    zip \
    && rm -rf /var/lib/apt/lists/*

ENV GODOT_VERSION "3.1.2"

RUN wget https://downloads.tuxfamily.org/godotengine/${GODOT_VERSION}/Godot_v${GODOT_VERSION}-stable_linux_server.64.zip \
    && mkdir ~/.cache \
    && mkdir -p ~/.config/godot \
    && mkdir -p ~/.local/share/godot/templates/${GODOT_VERSION}.stable \
    && unzip Godot_v${GODOT_VERSION}-stable_linux_server.64.zip \
    && mv Godot_v${GODOT_VERSION}-stable_linux_server.64 /usr/local/bin/godot \
    && rm -f Godot_v${GODOT_VERSION}-stable_linux_server.64.zip
