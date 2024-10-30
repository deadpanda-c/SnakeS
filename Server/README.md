# Server

This is the server side of the SnakeS game.  
It is written in cpp.

## Build

To build the server you need to have installed:

- CMake
- C++ compiler

To build the server you need to run the following commands:

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
docker build -t snakes-server .
docker run -p 42000:42000 snakes-server
```

Or you can use docker-compose:

```bash
docker compose up
```
