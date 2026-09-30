FROM ubuntu:24.04

WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    qt6-base-dev \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    qt6-wayland \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . .

WORKDIR /build
RUN qmake6 /src/XenoForge/XenoForge.pro
RUN make

CMD ["/build/XenoForge"]