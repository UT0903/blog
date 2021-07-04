FROM ubuntu:latest

# Copy hw4
COPY HW4/* /root/

ENV DEBIAN_FRONTEND="noninteractive"

# Update system and install packages
RUN apt-get update
RUN apt-get install build-essential clang bison flex \
	libreadline-dev gawk tcl-dev libffi-dev git \
	graphviz xdot pkg-config python3 libboost-system-dev \
	libboost-python-dev libboost-filesystem-dev zlib1g-dev

# Build Yosys
RUN wget -q https://github.com/YosysHQ/yosys/archive/yosys-0.9.tar.gz && \
    tar -xvzf yosys-0.9.tar.gz && \
    rm yosys-0.9.tar.gz
RUN cd yosys-0.9 && make && make install

# Cleanup
RUN apt-get autoremove -y && apt-get autoclean
RUN rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /var/log/*
