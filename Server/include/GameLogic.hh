/*
** File description:
** GameLogic
*/

#pragma once

#include <SFML/Network/TcpSocket.hpp>
#include <Snake.hh>
#include <array>
#include <vector>

struct Coord {
        uint x_pos{0};
        uint y_pos{0};
};

class GameLogic
{
    public:
        GameLogic();
        GameLogic(GameLogic const &to_copy) = default;
        GameLogic(GameLogic &&to_move) = default;
        ~GameLogic() = default;
        GameLogic &operator=(GameLogic const &to_copy) = default;
        GameLogic &operator=(GameLogic &&to_move) = default;

        void start_game_logic(std::array<sf::TcpSocket, 4> &clients, uint clients_number);

    private:
        bool m_game_running{true};
        uint m_height{30};
        uint m_width{30};
        Coord m_fruit{};
        std::vector<Snake> m_players;

        void generate_fruit();
        void create_players(uint clients_number);
        void update_game(std::array<sf::TcpSocket, 4> &clients, uint clients_number);
        void handle_clients(std::array<sf::TcpSocket, 4> &clients, uint clients_number);
        void handle_colision(std::array<sf::TcpSocket, 4> &clients, uint clients_number);
        void move_everyone(std::array<sf::TcpSocket, 4> &clients, uint clients_number);
        void handle_fruit(std::array<sf::TcpSocket, 4> &clients, uint clients_number);
};