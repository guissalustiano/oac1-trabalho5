FROM debian:12-slim

RUN apt update
RUN apt install -y linux-perf gcc make
RUN apt install -y python3 python3-pip python-is-python3
