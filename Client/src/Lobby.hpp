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

#include "Constants.hpp"
#include "Tools.hpp"
#include "Button.hpp"

#include "BinaryPacket.hpp"
#include "Communication.hpp"

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

        bool _gameStarted;

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
        bool _isClicking;
        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _cursor;

        // main window
        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _mainBackground;
        std::unique_ptr<Button> _connectButton;

        // connecting window
        bool _failed_connection;
        std::unique_ptr<Button> _cancelButton;
        std::unique_ptr<Button> _retryButton;

        // connected window
        std::unique_ptr<Button> _readyButton;
        int playerID;
        int playerCount;

        // binary library
        std::shared_ptr<BinaryPacket> _binaryPacket;
};

#endif // LOBBY_HPP
