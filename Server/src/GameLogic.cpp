/*
** File description:
** GameLogic
*/

#include <GameLogic.hh>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/SocketSelector.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <cstdint>
#include <ctime>

GameLogic::GameLogic()
{
    srand(time(nullptr));
}

void GameLogic::start_game_logic(std::array<sf::TcpSocket, 4> &clients, uint clients_number)
{
    sf::Clock clock{};
    generate_fruit();
    create_players(clients_number);
    update_game(clients, clients_number);
    for (size_t i{0}; i <= clients_number; i++) {
        m_udp_clients[i].bind(clients[i].getLocalPort());
        m_udp_clients[i].setBlocking(false);
    }

    while (m_game_running) {
        if (clock.getElapsedTime().asMilliseconds() > 300) {
            handle_colision(clients, clients_number);
            handle_clients(clients, clients_number);
            move_everyone(clients, clients_number);
            handle_fruit(clients, clients_number);
            update_game(clients, clients_number);
        }
    }
}

void GameLogic::generate_fruit()
{
    m_fruit.y_pos = {rand() % m_height};
    m_fruit.x_pos = {rand() % m_width};
}

void GameLogic::create_players(uint clients_number)
{
    static const constexpr std::array<Body, 4> begin_pos{
        Body{1, 1, orient::EAST}, Body{28, 28, orient::WEST}, Body{1, 28, orient::NORTH},
        Body{28, 1, orient::SOUTH}};

    for (uint i{0}; i <= clients_number; i++)
        m_players.emplace_back(begin_pos[i].s_pos_x, begin_pos[i].s_pos_y, begin_pos[i].s_orient,
                               i);
}

void GameLogic::update_game(std::array<sf::TcpSocket, 4> &clients, uint clients_number)
{
    BinaryPacket fruit_packet{BinaryPacket::FRUIT_STATUS};
    BinaryPacket player_packet{BinaryPacket::GAME_STATE};
    sf::Packet packet{};

    fruit_packet.addUint16(static_cast<short>(m_fruit.x_pos));
    fruit_packet.addUint16(static_cast<short>(m_fruit.y_pos));
    packet << fruit_packet.serialize();

    for (uint i{0}; i <= clients_number; i++) {
        auto port{clients[i].getRemotePort()};
        auto address{clients[i].getRemoteAddress()};
        m_udp_clients[i].send(packet, address, port);
    }
    packet.clear();

    player_packet.addString("");
    for (uint i{0}; i <= clients_number; i++)
        m_players[i].edit_packet(player_packet);
    packet << player_packet.serialize();
    for (uint i{0}; i <= clients_number; i++) {
        auto port{clients[i].getRemotePort()};
        auto address{clients[i].getRemoteAddress()};
        m_udp_clients[i].send(packet, address, port);
    }
}

void GameLogic::handle_clients(std::array<sf::TcpSocket, 4> &clients, uint clients_number)
{
    sf::Packet packet{};
    std::vector<uint8_t> serialize_data{};

    for (uint i{0}; i <= clients_number; i++) {
        auto port{clients[i].getRemotePort()};
        auto address{clients[i].getRemoteAddress()};
        if (m_udp_clients[i].receive(packet, address, port) == sf::Socket::Done) {
            if (packet >> serialize_data) {
                BinaryPacket unserialize_data{BinaryPacket::deserialize(serialize_data)};
                if (unserialize_data.getType() == BinaryPacket::PLAYER_ACTION) {
                    uint8_t id{unserialize_data.getByte(0)};
                    uint8_t direction{unserialize_data.getByte(1)};
                    direction >>= 6;
                    m_players[id].set_orient(static_cast<orient>(direction));
                }
            }
        }
    }
}

void GameLogic::handle_colision(std::array<sf::TcpSocket, 4> &clients, uint clients_number)
{
    sf::Packet packet{};

    for (uint i{0}; i <= clients_number; i++) {
        if (m_players[i].is_it_dead())
            continue;
        BinaryPacket unserialize_data{BinaryPacket::DEATH};
        if (m_players[i].is_colliding_wall(m_height, m_width)) {
            unserialize_data.addByte(static_cast<uint8_t>(i));
            packet << unserialize_data.serialize();
            for (uint i{0}; i <= clients_number; i++) {
                auto port{clients[i].getRemotePort()};
                auto address{clients[i].getRemoteAddress()};
                m_udp_clients[i].send(packet, address, port);
            }
            continue;
        }
        for (uint j{0}; j <= clients_number; j++) {
            if (m_players[j].is_it_dead())
                continue;
            if (m_players[j].is_colliding_it(m_players[i].get_head_pos()))
                unserialize_data.addByte(static_cast<uint8_t>(i));
            packet << unserialize_data.serialize();
            for (uint i{0}; i <= clients_number; i++) {
                auto port{clients[i].getRemotePort()};
                auto address{clients[i].getRemoteAddress()};
                m_udp_clients[i].send(packet, address, port);
            }
        }
        packet.clear();
    }
}

void GameLogic::move_everyone(std::array<sf::TcpSocket, 4> &clients, uint clients_number)
{
    for (uint i{0}; i <= clients_number; i++) {
        if (m_players[i].is_it_dead())
            continue;
        m_players[i].move();
    }
}
void GameLogic::handle_fruit(std::array<sf::TcpSocket, 4> &clients, uint clients_number)
{

    for (uint i{0}; i <= clients_number; i++) {
        if (m_players[i].is_it_dead())
            continue;
        Body tmp{m_players[i].get_head_pos()};
        if (tmp.s_pos_x == m_fruit.x_pos && tmp.s_pos_y == m_fruit.y_pos) {
            /*            sf::Packet packet{};
                        BinaryPacket fruit_packet{BinaryPacket::FRUIT_STATUS};
                        fruit_packet.addUint16(static_cast<short>(m_fruit.x_pos));
                        fruit_packet.addUint16(static_cast<short>(m_fruit.y_pos));
                        packet << fruit_packet.serialize();

                        for (uint j{0}; j <= clients_number; j++)
                            clients[j].send(packet);
                        packet.clear();
                        BinaryPacket player_upgrade{BinaryPacket::EAT_FRUIT};
                        player_upgrade.addByte(static_cast<uint8_t>(i));
                        packet << player_upgrade.serialize();
                        for (uint j{0}; j <= clients_number; j++)
                            clients[j].send(packet);
                        packet.clear(); */
            m_players[i].eat_apple();
            generate_fruit();
        }
    }
}
