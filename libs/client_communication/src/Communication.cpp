#include "Communication.hpp"

Communication::Communication() : _ip("127.0.0.1"), _port(4242)
{
  this->init();
}

Communication::Communication(std::string ip, unsigned short port) : _ip(ip), _port(port)
{
  this->init();
}

Communication::~Communication()
{
  std::cout << "Closing connection..." << std::endl;
}

void Communication::connectToServer()
{
  if (connect(_sockfd, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr)) < 0)
    throw ConnectionError(CONNECTION_ERROR);
  std::cout << "Connected to server" << std::endl;
}

void Communication::sendToServer(std::string message)
{
  if (send(_sockfd, message.c_str(), message.size(), 0) < 0)
    throw ConnectionError(SEND_ERROR);
  std::cout << "Message sent to server" << std::endl;
}

std::string Communication::receiveFromServer()
{
  char buffer[1024] = {0};
  if (recv(_sockfd, buffer, 1024, 0) < 0)
    throw ConnectionError(RECEIVE_ERROR);
  std::cout << "Message received from server" << std::endl;
  return std::string(buffer);
}

void Communication::init()
{
  _sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (_sockfd < 0)
    throw ConnectionError(SOCKET_INITIALIZATION_ERROR);

  _serverAddr.sin_family = AF_INET;
  _serverAddr.sin_port = htons(_port);
  _serverAddr.sin_addr.s_addr = inet_addr(_ip.c_str());

  std::cout << "Connecting to server..." << std::endl;
}
