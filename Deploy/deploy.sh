#!/bin/bash
docker pull coolPath/OK
docker stop okName && docker rm okName
docker run --name okName -d -p 10:50/udp coolPath/OK && exit 0
