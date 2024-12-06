#ifndef CORE_HPP
#define CORE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"
#include "Lobby.hpp"

class Core {
    public:
        Core(uint windowSize, uint gameSize, std::pair<std::string, ushort> ipPort);
        Core();
        ~Core();

        void setWindowSize(uint windowSize);
        void setGameSize(uint gameSize);
        void setIpPort(std::pair<std::string, ushort> ipPort);
        int run();

    private:
        int _setup();

        uint _windowSize;
        uint _gameSize;

        std::shared_ptr<std::pair<std::string, ushort>> _ipPort;
        std::shared_ptr<sf::RenderWindow> _window;
        std::shared_ptr<sf::TcpSocket> _socket;
        
        Game _game;
        Lobby _lobby;

};

#endif // CORE_HPP