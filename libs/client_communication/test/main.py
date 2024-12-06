#!/bin/python3

from socket import socket

if __name__ == "__main__":
    server = socket()
    server.bind(("127.0.0.1", 4242))
    server.listen(5)

    while True:
        client, addr = server.accept()
        print(f"Connection from {addr}")
        client.send(b"Hello, World!")
        msg = client.recv(1024)
        print(msg.decode())
        client.close()

