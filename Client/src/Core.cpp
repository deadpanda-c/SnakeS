#include "Core.hpp"

Core::Core(std::pair<uint, uint> windowSize, std::pair<uint, uint> gameSize, std::pair<std::string, ushort> ipPort) {
    _windowSize = windowSize;
    _gameSize = gameSize;
    _ipPort = std::make_shared<std::pair<std::string, ushort>>(ipPort);
}

Core::Core() {}

Core::~Core() {
    if (_socket->getRemoteAddress() != sf::IpAddress::None) _socket->disconnect();
    if (_window) _window->close();
}

void Core::setWindowSize(std::pair<uint, uint> windowSize) {
    _windowSize = windowSize;
}

void Core::setGameSize(std::pair<uint, uint> gameSize) {
    _gameSize = gameSize;
}

void Core::setIpPort(std::pair<std::string, ushort> ipPort) {
    _ipPort = std::make_shared<std::pair<std::string, ushort>>(ipPort);
}

int Core::_setup() {
    sf::Image icon;

    if (!_windowSize.first || !_windowSize.second || !_gameSize.first || !_gameSize.second) {
        std::cerr << "Window size and game size must be set before running the game" << std::endl;
        return 1;
    }
    _socket = std::make_shared<sf::TcpSocket>();
    
    icon.loadFromFile(Constants::APPLE);
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(_windowSize.first, _windowSize.second), "SnakeS");
    _window->setFramerateLimit(240);
    _window->setIcon(16, 16, icon.getPixelsPtr());
    _window->setKeyRepeatEnabled(false);
    _window->setMouseCursorVisible(false);

    _game.setSocket(_socket);
    _game.setIpPort(_ipPort);
    _game.setWindow(_window);
    _game.setGameSize(sf::Vector2<uint>(_gameSize.first, _gameSize.second));

    _lobby.setSocket(_socket);
    _lobby.setIpPort(_ipPort);
    _lobby.setWindow(_window);

    return 0;
}

int Core::run() {
    if (_setup()) return 1;
    if (_lobby.run()) return 0;
    std::cout << "Game started" << std::endl;
    if (_game.run()) return 0;
    return 0;
}