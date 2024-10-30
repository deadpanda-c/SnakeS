# Client

This is the client side of the SnakeS game.  
It is written in cpp and uses the [SFML](https://www.sfml-dev.org/) library.

## Build

To build the client you need to have installed:

- git
- CMake
- C++ compiler
- SFML

To install SFML dependencies on Ubuntu you can run the following command:

```bash
sudo apt update
sudo apt install \
    libfreetype-dev \
    libfreetype6 \
    libfreetype6-dev \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libdrm-dev \
    libgbm-dev
```

To build the client you need to run the following commands:

```bash
cmake -B build
cmake --build build
```

## Deploy


To deploy the server you need to have installed:

- docker
- docker-compose (optional)

To deploy the server you need to run the following commands:

```bash
docker build -t c_snakes .
docker run -p 5000:5000 \
    -e DISPLAY \
    --rm -ti --net=host \
    -v /tmp/.X11-unix/:/tmp/.X11-unix \
    --name c_snakes c_snakes
```

Or you can use docker-compose:

```bash
docker compose up
```
