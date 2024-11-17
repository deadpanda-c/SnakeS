/*
** SnakeS/Server/src
** File description:
** main
*/

#include <SFML/Network.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <Server.hh>

int main(int argc, char **argv)
{
    // Server server{static_cast<unsigned short>(argc), argv[1]};
    Server server{8000, std::string{"127.0.0.1"}};
    server.launch();
    return 0;
}
