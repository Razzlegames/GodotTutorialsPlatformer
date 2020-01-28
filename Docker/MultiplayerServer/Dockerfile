FROM razzlegames/godot-server:ubuntu-first
LABEL author="razzlegames@gmail.com"

EXPOSE 1507/udp

RUN useradd godotuser -m
COPY resources.pck /home/godotuser/

WORKDIR /home/godotuser/

CMD godot -v -d --main-pack resources.pck MultiPlayer/ChatRoom.tscn >> manualLogFile.log 2>&1

