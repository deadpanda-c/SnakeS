/*
** File description:
** Server
*/

#include <SFML/Network.hpp>
#include "Server.hpp"

Server::Server(unsigned short port, const std::string &addr) {
  m_server.listen(port, sf::IpAddress{addr});
  m_server.setBlocking(false);
}

void Server::launch() {
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
