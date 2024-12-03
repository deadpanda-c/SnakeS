#ifndef CORE_HPP
#define CORE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"
#include "Lobby.hpp"

class Core {
    public:
        Core(std::pair<uint, uint> windowSize, std::pair<uint, uint> gameSize, std::pair<std::string, ushort> ipPort);
        Core();
        ~Core();

        void setWindowSize(std::pair<uint, uint> windowSize);
        void setGameSize(std::pair<uint, uint> gameSize);
        void setIpPort(std::pair<std::string, ushort> ipPort);
        int run();

    private:
        int _setup();

        std::pair<uint, uint> _windowSize;
        std::pair<uint, uint> _gameSize;

        std::shared_ptr<std::pair<std::string, ushort>> _ipPort;
        std::shared_ptr<sf::RenderWindow> _window;
        std::shared_ptr<sf::TcpSocket> _socket;
        
        Game _game;
        Lobby _lobby;

};

#endif // CORE_HPP