#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>


#define RECEIVE_ERROR "Error receiving message from server"
#define SEND_ERROR "Error sending message to server"
#define CONNECTION_ERROR "Connection to server failed"
#define SOCKET_INITIALIZATION_ERROR "Socket initialization failed"

class Communication {
  public:
    enum class ConnectionType {
      TCP,
      UDP
    };
    class ConnectionError : public std::exception {
      public:
        ConnectionError(const char *msg) : _msg(msg) {}
        const char *what() const noexcept { return _msg; }
      private:
        const char *_msg;
    };
    Communication();
    Communication(std::string ip, unsigned short port, Communication::ConnectionType type);
    ~Communication();


    void connectToServer();
    void sendToServer(std::string message);
    std::string receiveFromServer();
  private:
    ConnectionType _comm_type;
    std::string _ip;
    unsigned short _port;

    int _sockfd;
    struct sockaddr_in _serverAddr;
    char _buffer[1024];

    void init();

};
