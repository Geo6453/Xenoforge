FROM ubuntu:24.04

WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    qt6-base-dev \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    qt6-wayland \
    && rm -rf /var/lib/apt/lists/*

COPY . .

RUN qmake6 XenoForge\XenoForge.pro
RUN make -j$(nproc)

CMD ["XenoForge"]