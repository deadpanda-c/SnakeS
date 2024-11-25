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
    _windowSize = _window->getSize();
    _state = LobbyStateEnum::MAIN;
    _scale = _windowSize.x / 100;
    _font.loadFromFile(FONT);
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

    _window->display();
}

void Lobby::_drawMain() {
    sf::RectangleShape button(sf::Vector2f(50 * _scale, 12.5 * _scale));
    sf::Text buttonText("Connect", _font, 8 * _scale);

    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(34 * _scale, 66 * _scale);
    button.setPosition(25 * _scale, 65 * _scale);
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(10);

    if (button.getGlobalBounds().contains(_mousePos.x, _mousePos.y)) {
        button.setFillColor(sf::Color(64, 64, 64));
        if (_is_clicking) {
            _state = LobbyStateEnum::CONNECTING;
            _failed_connection = false;
            _is_clicking = false;
            std::cout << "Change lobby state: " << (std::array<std::string, 4>{"MAIN", "CONNECTING", "CONNECTED", "READY"}[_state]) << std::endl;
        }
    } else {
        button.setFillColor(sf::Color::Black);
    }

    _window->draw(button);
    _window->draw(buttonText);
}

void Lobby::_drawConnecting() {
    // try to connect to the server, if it fails, display a retry button
    if (!_failed_connection) {
        sf::Socket::Status status = _socket->connect(_ipPort->first, _ipPort->second);

        if (status == sf::Socket::Done) {
            _state = LobbyStateEnum::CONNECTED;
            std::cout << "Change lobby state: " << (std::array<std::string, 4>{"MAIN", "CONNECTING", "CONNECTED", "READY"}[_state]) << std::endl;
        } else {
            std::cout << "Failed to connect to the server, socket status: " << status << std::endl;
            _failed_connection = true;
        }
    } else {
        sf::RectangleShape retryButton(sf::Vector2f(50 * _scale, 12.5 * _scale));
        sf::Text retryButtonText("Retry", _font, 8 * _scale);
        sf::Text errorText("Failed to connect to the server", _font, 6 * _scale);

        retryButtonText.setFillColor(sf::Color::White);
        retryButtonText.setPosition(38 * _scale, 60 * _scale);
        retryButton.setPosition(25 * _scale, 59 * _scale);
        retryButton.setOutlineColor(sf::Color::White);
        retryButton.setOutlineThickness(10);

        errorText.setFillColor(sf::Color::White);
        errorText.setPosition(6 * _scale, 45 * _scale);

        if (retryButton.getGlobalBounds().contains(_mousePos.x, _mousePos.y)) {
            retryButton.setFillColor(sf::Color(64, 64, 64));
            if (_is_clicking) {
                _failed_connection = false;
                _is_clicking = false;
            }
        } else {
            retryButton.setFillColor(sf::Color::Black);
        }

        _window->draw(retryButton);
        _window->draw(retryButtonText);
        _window->draw(errorText);

        // draw a cancel button
        sf::RectangleShape cancelButton(sf::Vector2f(50 * _scale, 12.5 * _scale));
        sf::Text cancelButtonText("Cancel", _font, 8 * _scale);

        cancelButtonText.setFillColor(sf::Color::White);
        cancelButtonText.setPosition(36 * _scale, 80 * _scale);
        cancelButton.setPosition(25 * _scale, 79 * _scale);
        cancelButton.setOutlineColor(sf::Color::White);
        cancelButton.setOutlineThickness(10);

        if (cancelButton.getGlobalBounds().contains(_mousePos.x, _mousePos.y)) {
            cancelButton.setFillColor(sf::Color(64, 64, 64));
            if (_is_clicking) {
                _state = LobbyStateEnum::MAIN;
                _is_clicking = false;
                std::cout << "Change lobby state: " << (std::array<std::string, 4>{"MAIN", "CONNECTING", "CONNECTED", "READY"}[_state]) << std::endl;
            }
        } else {
            cancelButton.setFillColor(sf::Color::Black);
        }

        _window->draw(cancelButton);
        _window->draw(cancelButtonText);
    }
}

void Lobby::_drawConnected() {
    // display a "ready" button
    // if the user clicks on "ready" button, change the state to READY
    // if the user clicks on "cancel" button, change the state to MAIN
    // need to display the snakes that connects to the server
    // need to display the number of players connected
}

void Lobby::_drawReady() {
    // in the ready state, the user waits for the game to start
    // display a "cancel" button to cancel the ready state
}

void Lobby::_update() {
    while (_window->pollEvent(_event)) {
        _mousePos = sf::Mouse::getPosition(*_window);
        if (_event.type == sf::Event::Closed) {
            _window->close();
        }
        if (_event.type == sf::Event::KeyPressed) {
            switch (_event.key.code) {
                case sf::Keyboard::Escape:
                    _window->close();
                    break;
                default:
                    break;
            }
        }
        if (_event.type == sf::Event::MouseButtonPressed) {
            if (_event.mouseButton.button == sf::Mouse::Left) {
                _lastClick = _mousePos;
                _is_clicking = true;
            }
        }
    }
}

int Lobby::run() {
    _setup();

    while (_window->isOpen()) {
        _update();
        _draw();
    }
    return 0;
}