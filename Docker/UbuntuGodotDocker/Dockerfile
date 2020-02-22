FROM ubuntu:bionic
LABEL author="razzlegames@gmail.com"

RUN apt-get update && apt-get install -y --fix-missing --no-install-recommends \
    ca-certificates \
    git \
    python3 \
    python3-cryptography \
    python3-pip \
    unzip \
    wget \
    zip \
    netcat \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install gitpython

ENV GODOT_VERSION "3.1.2"

RUN wget https://downloads.tuxfamily.org/godotengine/${GODOT_VERSION}/Godot_v${GODOT_VERSION}-stable_linux_server.64.zip \
    && mkdir -p ~/.cache \
    && mkdir -p ~/.config/godot \
    && unzip Godot_v${GODOT_VERSION}-stable_linux_server.64.zip \
    && mv Godot_v${GODOT_VERSION}-stable_linux_server.64 /usr/local/bin/godot \
    && rm -f Godot_v${GODOT_VERSION}-stable_linux_server.64.zip
