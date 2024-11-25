#ifndef LOBBY_HPP
#define LOBBY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>
#include <memory>

#include "Enum.hpp"

#define FONT "assets/Minecraft.ttf"

class Lobby
{
    public:
        Lobby();
        ~Lobby();

        void setWindow(std::shared_ptr<sf::RenderWindow> window);
        void setSocket(std::shared_ptr<sf::TcpSocket> socket);
        void setIpPort(std::shared_ptr<std::pair<std::string, ushort>> ipPort);
        int run();

    private:
        void _setup();
        void _draw();
        void _update();

        void _drawMain();
        void _drawConnecting();
        void _drawConnected();
        void _drawReady();

        sf::Font _font;
        LobbyStateEnum _state;
        std::shared_ptr<sf::TcpSocket> _socket;
        std::shared_ptr<sf::RenderWindow> _window;
        std::shared_ptr<std::pair<std::string, ushort>> _ipPort;
        sf::Event _event;
        sf::Vector2<uint> _windowSize;
        sf::Vector2<uint> _gameSize;
        float _scale;

        sf::Vector2i _mousePos;
        sf::Vector2i _lastClick;
        bool _is_clicking;

        // main window

        // connecting window
        bool _failed_connection;


};

#endif // LOBBY_HPP
