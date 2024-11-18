/*
** File description:
** Server
*/

#pragma once

#include "GameLogic.hpp"
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <string>
#include <array>

class Server
{
    public:
        Server() = delete;
        Server(unsigned short port = 8000, const std::string &addr = "127.0.0.1");
        Server(Server const &to_copy) = delete;
        Server(Server &&to_move) = delete;
        ~Server() = default;
        Server &operator=(Server const &to_copy) = delete;
        Server &operator=(Server &&to_move) = delete;

        void launch();

    private:
        sf::TcpListener m_server;
        std::array<sf::TcpSocket, 4> m_clients{};
        uint m_clients_number{0};
        GameLogic m_game_logic;
};
