ARG VARIANT="22.04"
FROM ubuntu:${VARIANT} as base

ARG DEBIAN_FRONTEND=noninteractive

# setup all the dependencies for F' and the TM4C
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    cmake \
    ffmpeg \
    libsm6 \
    libxext6 \
    libtool \
    pkg-config \
    libusb-1.0-0-dev \
    lm4flash \
    automake \
    libncurses-dev \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    gdb-multiarch \
    graphviz \
    stlink-tools \
    && rm -rf /var/lib/apt/lists/* \
    && cd /root \
    && git clone --depth 1 --j $(nproc) https://git.code.sf.net/p/openocd/code openocd-code \
    && cd openocd-code \
    && ./bootstrap \
    && ./configure --enable-ti-icdi \
    && make -j $(nproc) \
    && make install \
    && cd .. \
    && rm -rf openocd-code

# if using GDB on the host instead of the container
EXPOSE 50000