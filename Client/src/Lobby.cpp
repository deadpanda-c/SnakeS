#include "Lobby.hpp"

Lobby::Lobby() {}

Lobby::~Lobby() {}

void Lobby::setWindow(std::shared_ptr<sf::RenderWindow> window) {
    _window = window;
}

void Lobby::setSocket(std::shared_ptr<sf::TcpSocket> socket) {
    _socket = socket;
}

void Lobby::setIpPort(std::shared_ptr<std::pair<std::string, ushort>> ipPort) {
    _ipPort = ipPort;
}

void Lobby::_setup() {
    _binaryPacket = std::make_shared<BinaryPacket>(BinaryPacket::PLAYER_JOIN);
    _gameStarted = false;
    _windowSize = _window->getSize();
    _state = LobbyStateEnum::MAIN;
    _scale = _windowSize.x / 128.0;
    _font.loadFromFile(Constants::FONT);

    _connectButton = std::make_unique<Button>(sf::Vector2f(32 * _scale, 95 * _scale), sf::Vector2f(64 * _scale, 12.5 * _scale), "Connect", 8 * _scale);
    _retryButton = std::make_unique<Button>(sf::Vector2f(32 * _scale, 85 * _scale), sf::Vector2f(64 * _scale, 12.5 * _scale), "Retry", 8 * _scale);
    _cancelButton = std::make_unique<Button>(sf::Vector2f(32 * _scale, 105 * _scale), sf::Vector2f(64 * _scale, 12.5 * _scale), "Cancel", 8 * _scale);
    _readyButton = std::make_unique<Button>(sf::Vector2f(32 * _scale, 80 * _scale), sf::Vector2f(64 * _scale, 12.5 * _scale), "Ready", 8 * _scale);

    _mainBackground = Tools::loadSprite(Constants::MAIN_BACKGROUND, _scale);
    _mainBackground.second.setPosition(_windowSize.x / 2, _windowSize.y / 2);

    _cursor = Tools::loadSprite(Constants::CURSOR, _scale / 2.0);
}

void Lobby::_draw() {
    _window->clear(sf::Color(32, 32, 32));

    switch (_state) {
        case LobbyStateEnum::MAIN:
            _drawMain();
            break;
        case LobbyStateEnum::CONNECTING:
            _drawConnecting();
            break;
        case LobbyStateEnum::CONNECTED:
            _drawConnected();
            break;
        case LobbyStateEnum::READY:
            _drawReady();
            break;
    }

    _cursor.second.setPosition(_mousePos.x, _mousePos.y);
    _window->draw(_cursor.second);
    _window->display();
}

void Lobby::_drawMain() {
    _window->draw(_mainBackground.second);

    bool status = _connectButton->update(_mousePos, _isClicking);
    _connectButton->draw(*_window);

    if (status) {
        _state = LobbyStateEnum::CONNECTING;
        _failed_connection = false;
        _isClicking = false;
//        std::cout << "Change lobby state: " << (std::array<std::string, 4>{"MAIN", "CONNECTING", "CONNECTED", "READY"}[_state]) << std::endl;
    }
}

void Lobby::_drawConnecting() {
    // try to connect to the server, if it fails, display a retry button
    if (!_failed_connection) {
        sf::Socket::Status status = _socket->connect(_ipPort->first, _ipPort->second);

        if (status == sf::Socket::Done) {
            _state = LobbyStateEnum::CONNECTED;
 //           std::cout << "Change lobby state: " << (std::array<std::string, 4>{"MAIN", "CONNECTING", "CONNECTED", "READY"}[_state]) << std::endl;
        } else {
            std::cout << "Failed to connect to the server, socket status: " << status << std::endl;
            _failed_connection = true;
        }
    } else {
        bool statusRetry = _retryButton->update(_mousePos, _isClicking);
        _retryButton->draw(*_window);

        if (statusRetry) {
            _failed_connection = false;
            _isClicking = false;
        }

        bool statusCancel = _cancelButton->update(_mousePos, _isClicking);
        _cancelButton->draw(*_window);

        if (statusCancel) {
            _state = LobbyStateEnum::MAIN;
            _isClicking = false;
  //          std::cout << "Change lobby state: " << (std::array<std::string, 4>{"MAIN", "CONNECTING", "CONNECTED", "READY"}[_state]) << std::endl;
        }

    }
}

void Lobby::_drawConnected() {
    // display a "ready" button
    // if the user clicks on "ready" button, change the state to READY
    // if the user clicks on "cancel" button, change the state to MAIN
    // need to display the snakes that connects to the server
    // need to display the number of players connected

    // listen to the server for the number of players connected and the player ID

    bool statusReady = _readyButton->update(_mousePos, _isClicking);
    _readyButton->draw(*_window);

    if (statusReady) {
        _state = LobbyStateEnum::READY;
        _isClicking = false;
   //     std::cout << "Change lobby state: " << (std::array<std::string, 4>{"MAIN", "CONNECTING", "CONNECTED", "READY"}[_state]) << std::endl;
    }
}

void Lobby::_drawReady() {
    // in the ready state, the user waits for the game to start
    // display a "cancel" button to cancel the ready state
}

void Lobby::_update() {
    while (_window->pollEvent(_event)) {
        _mousePos = sf::Mouse::getPosition(*_window);
        switch (_event.type)
        {
        case sf::Event::Closed:
            _window->close();
            break;
        case sf::Event::KeyPressed:
            switch (_event.key.code) {
                case sf::Keyboard::Escape:
                    _window->close();
                    break;
                default:
                    break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (_event.mouseButton.button == sf::Mouse::Left) {
                _lastClick = _mousePos;
                _isClicking = true;
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (_event.mouseButton.button == sf::Mouse::Left) {
                _isClicking = false;
            }
            break;
        default:
            break;
        }
    }
}

int Lobby::run() {
    _setup();

    while (_window->isOpen()) {
        _update();
        _draw();
        if (_gameStarted) {
            return 0;
        }
    }
    return 1;
}
