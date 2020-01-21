FROM razzlegames/godot-server:ubuntu-first
LABEL author="razzlegames@gmail.com"

ENV GODOT_VERSION "3.1.2"

RUN wget https://downloads.tuxfamily.org/godotengine/${GODOT_VERSION}/Godot_v${GODOT_VERSION}-stable_export_templates.tpz \
    && mkdir -p ~/.config/godot \
    && mkdir -p ~/.local/share/godot/templates/${GODOT_VERSION}.stable \
    && unzip Godot_v${GODOT_VERSION}-stable_export_templates.tpz \
    && mv templates/* ~/.local/share/godot/templates/${GODOT_VERSION}.stable \
    && rm -f Godot_v${GODOT_VERSION}-stable_export_templates.tpz 

RUN godot -v --export "Linux/X11" ../build/linux/$EXPORT_NAME.x86_64
