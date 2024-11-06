#include "Core.hpp"

Core::Core(sf::Vector2<int> windowSize, sf::Vector2<int> gameSize, std::pair<std::string, int> ipPort) {
    _windowSize = windowSize;
    _gameSize = gameSize;

    _socket.connect(ipPort.first, ipPort.second);
}

Core::Core() {}

Core::~Core() {
    _socket.disconnect();
    _window.close();
}

void Core::setWindowSize(sf::Vector2<int> windowSize) {
    _window.setSize(sf::Vector2u(windowSize.x, windowSize.y));
}

void Core::setGameSize(sf::Vector2<int> gameSize) {
    _gameSize = gameSize;
}

int Core::setIpPort(std::pair<std::string, unsigned short> ipPort) {
    sf::Socket::Status status = _socket.connect(ipPort.first, ipPort.second);

    if (status != sf::Socket::Done) {
        std::vector<std::string> statusName = {"Done", "NotReady", "Partial", "Disconnected", "Error"};
        std::cerr << "Failed to connect to the server: " << statusName[status] << std::endl;
        return 1;
    }
    return 0;
}

void Core::run() {
    _window.create(sf::VideoMode(_windowSize.x, _windowSize.y), "Snake");
    _window.setFramerateLimit(60);
    while (_window.isOpen()) {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                _window.close();
            }
        }
    }
}

