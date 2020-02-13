FROM ubuntu:cosmic
LABEL author="razzlegames@gmail.com"

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    git \
    python \
    python-openssl \
    unzip \
    wget \
    zip \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y --no-install-recommends \
    ssh \
    && rm -rf /var/lib/apt/lists/*

ADD ./get-docker.sh get-docker.sh
RUN chmod +x get-docker.sh \
    && ./get-docker.sh \
    && rm -rf /var/lib/apt/lists/*

ENV GODOT_VERSION "3.1.2"

RUN wget https://downloads.tuxfamily.org/godotengine/${GODOT_VERSION}/Godot_v${GODOT_VERSION}-stable_linux_headless.64.zip \
    && wget https://downloads.tuxfamily.org/godotengine/${GODOT_VERSION}/Godot_v${GODOT_VERSION}-stable_export_templates.tpz \
    && mkdir ~/.cache \
    && mkdir -p ~/.config/godot \
    && mkdir -p ~/.local/share/godot/templates/${GODOT_VERSION}.stable \
    && unzip Godot_v${GODOT_VERSION}-stable_linux_headless.64.zip \
    && mv Godot_v${GODOT_VERSION}-stable_linux_headless.64 /usr/local/bin/godot \
    && unzip Godot_v${GODOT_VERSION}-stable_export_templates.tpz \
    && mv templates/* ~/.local/share/godot/templates/${GODOT_VERSION}.stable \
    && rm -f Godot_v${GODOT_VERSION}-stable_export_templates.tpz Godot_v${GODOT_VERSION}-stable_linux_headless.64.zip

