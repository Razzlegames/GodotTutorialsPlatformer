#!/bin/python3

import sys
import argparse

parser = argparse.ArgumentParser()

parser.add_argument("-s", "--server", help="Server IP to deploy to", required=True)
parser.add_argument("-n", "--name", help="name of docker image, used while running locally", required=True)
parser.add_argument("-a", "--dockerPath", help="full path to docker image, in dockerHub", required=True )
parser.add_argument("-hp", "--hostPort", help="Port mapped to host, from docker container", required=True)
parser.add_argument("-cp", "--containerPort", help="Port mapped to container, from host", required=True)
parser.add_argument("-pr", "--protocol", help="Port mapped to container, from host", required=True)

args = parser.parse_args()

fileName = "deploy.sh"

with open(fileName, 'w') as file:
    for line in ["#!/bin/bash",
                 "docker pull " + args.dockerPath,
                 "docker stop " + args.name + " && docker rm " + args.name,
                 "docker run --name " + args.name + " -d -p " + args.hostPort + ":" +
                 args.containerPort + "/" + args.protocol + " " + args.dockerPath + " && exit 0"]:

        file.write(line + "\n")

print("Created File:\n")

with open(fileName) as file:
    print(file.read())

