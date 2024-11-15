# Server

This is the server side of the SnakeS game.  
It is written in cpp.

## Build

To build the server you need to have installed:

- CMake
- C++ compiler

To build the server you need to run the following commands from the **root** directory:

```bash
cmake -B build -D ONLY_SERVER=true
cmake --build build
```

## Deploy

To deploy the server you need to have installed:

- docker
- docker-compose (optional)

To deploy the server you need to run the following commands from the **root** directory:

```bash
docker build -f ServerDockerfile -t snakes-server .
docker run -p 42000:42000 snakes-server
```

Or you can use docker-compose:

```bash
docker compose up
```

> **Note:**
> The docker-compose will also deploy the client.

## Usage

To run the server you need to run the following command:

```bash
./build/bin/s_snakes
```
