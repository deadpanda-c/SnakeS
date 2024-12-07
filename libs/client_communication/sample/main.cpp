#include <iostream>
#include "Communication.hpp"

int main(void)
{
  std::cout << "Client" << std::endl;
  Communication comm;

  comm.connectToServer();
  std::cout << "Server: " << comm.receiveFromServer() << std::endl;
  comm.sendToServer("Hello Server!");
  return 0;
}
