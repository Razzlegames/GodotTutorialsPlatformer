FROM razzlegames/godot-server:ubuntu-first
LABEL author="razzlegames@gmail.com"

RUN useradd godotuser -m

COPY resources.pck /home/godotuser/

WORKDIR /home/godotuser/

CMD godot -v --main-pack resources.pck MultiPlayer/ChatRoom.tscn

