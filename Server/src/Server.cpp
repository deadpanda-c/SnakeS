/*
** File description:
** Server
*/

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <Server.hh>

Server::Server(unsigned short port, const std::string &addr)
{
    m_server.listen(8000, sf::IpAddress{"127.0.0.1"});
    m_server.setBlocking(false);
}

void Server::launch()
{
    time_t start = time(nullptr);
    time_t end = time(nullptr);

    while ((m_clients_number < 1 || end - start < 30) && m_clients_number < 4) {
        if (m_server.accept(m_clients[m_clients_number]) == sf::Socket::Done) {
            m_clients[m_clients_number].setBlocking(false);
            m_clients_number++;
        }
        end = time(nullptr);
    }
    m_game_logic.start_game_logic(m_clients, m_clients_number);
}
