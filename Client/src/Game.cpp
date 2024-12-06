#include "Game.hpp"

Game::Game() {}

Game::~Game() {}

void Game::setGameSize(sf::Vector2<uint> gameSize) {
    _gameSize = gameSize;
}

void Game::setSocket(std::shared_ptr<sf::TcpSocket> socket) {
    _socket = socket;
}

void Game::setIpPort(std::shared_ptr<std::pair<std::string, ushort>> ipPort) {
    _ipPort = ipPort;
}

void Game::setWindow(std::shared_ptr<sf::RenderWindow> window) {
    _window = window;
}

void Game::_setup() {
    _windowSize = _window->getSize();
    _scale = _windowSize.x / _gameSize.x;

    // load all the sprites and textures
    _spriteMiddleSnake = Tools::loadSprite(Constants::SNAKE_MIDDLE, _scale / Constants::SPRITE_SIZE);
    _spriteHeadSnake = Tools::loadSprite(Constants::SNAKE_HEAD, _scale / Constants::SPRITE_SIZE);
    _spriteTailSnake = Tools::loadSprite(Constants::SNAKE_TAIL, _scale / Constants::SPRITE_SIZE);
    _spriteAngleSnake = Tools::loadSprite(Constants::SNAKE_ANGLE, _scale / Constants::SPRITE_SIZE);
    _spriteApple = Tools::loadSprite(Constants::APPLE, _scale / Constants::SPRITE_SIZE);

    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 20; i++) {
            _setSnake(j * 20 + i, {
                {i, j * 3 + 1},
                {i, j * 3 + 2},
                {i, j * 3 + 3},
            });
        }
    }
    _setApple({0, 0});
}

void Game::_draw() { // todo: handle of the snake is shorter than 3
    _window->clear();
    // draw the grid for debug purposes
    for (uint i = 0; i <= _gameSize.x; i++) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(i * _scale, 0)),
            sf::Vertex(sf::Vector2f(i * _scale, _windowSize.y))
        };
        line[0].color = sf::Color(255, 255, 255, 64);
        line[1].color = sf::Color(255, 255, 255, 64);
        _window->draw(line, 2, sf::Lines);
    }
    for (uint i = 0; i <= _gameSize.y; i++) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, i * _scale)),
            sf::Vertex(sf::Vector2f(_windowSize.x, i * _scale))
        };
        line[0].color = sf::Color(255, 255, 255, 64);
        line[1].color = sf::Color(255, 255, 255, 64);
        _window->draw(line, 2, sf::Lines);
    }

    for (std::vector<sf::Vector2i> &snake : _posSnakes) {
        if (snake.empty()) continue;

        // set the color of the snake depending on its id. the color will be a gradient from red to green to blue
        float hue = ((&snake - &_posSnakes[0]) * 1.0f / (_posSnakes.size() + 1)) + (1.0f / (_posSnakes.size() + 1));
        auto colorTuple = Tools::HSVtoRGB(hue, 1, 1);
        sf::Color color(std::get<0>(colorTuple), std::get<1>(colorTuple), std::get<2>(colorTuple));

        _spriteAngleSnake.second.setColor(color);
        _spriteMiddleSnake.second.setColor(color);
        _spriteHeadSnake.second.setColor(color);
        _spriteTailSnake.second.setColor(color);

        // draw the head
        sf::Vector2i &headPos = snake.front();
        sf::Vector2i &nextPos = snake[1];
        if (headPos.x < nextPos.x) _spriteHeadSnake.second.setRotation(0);
        else if (headPos.x > nextPos.x) _spriteHeadSnake.second.setRotation(180);
        else if (headPos.y < nextPos.y) _spriteHeadSnake.second.setRotation(90);
        else if (headPos.y > nextPos.y) _spriteHeadSnake.second.setRotation(270);
        _spriteHeadSnake.second.setPosition(_scale * (headPos.x + 0.5), _scale * (headPos.y + 0.5));
        _window->draw(_spriteHeadSnake.second);

        // draw the body
        for (size_t i = 1; i < snake.size() - 1; ++i) {
            sf::Vector2i &prevPos = snake[i - 1];
            sf::Vector2i &currPos = snake[i];
            sf::Vector2i &nextPos = snake[i + 1];

            if ((prevPos.x == currPos.x && currPos.x == nextPos.x) || 
                (prevPos.y == currPos.y && currPos.y == nextPos.y)) { // straight segment
                if (prevPos.x != currPos.x) _spriteMiddleSnake.second.setRotation(0);
                else _spriteMiddleSnake.second.setRotation(90);
                _spriteMiddleSnake.second.setPosition(_scale * (currPos.x + 0.5), _scale * (currPos.y + 0.5));
                _window->draw(_spriteMiddleSnake.second);
            } else { // angle segment
                if ((prevPos.x < currPos.x && currPos.y < nextPos.y) || (prevPos.y > currPos.y && currPos.x > nextPos.x)) _spriteAngleSnake.second.setRotation(180); // 1 - 7
                else if ((prevPos.x > currPos.x && currPos.y < nextPos.y) || (prevPos.y > currPos.y && currPos.x < nextPos.x)) _spriteAngleSnake.second.setRotation(90); // 4 - 8
                else if ((prevPos.x > currPos.x && currPos.y > nextPos.y) || (prevPos.y < currPos.y && currPos.x < nextPos.x)) _spriteAngleSnake.second.setRotation(0); // 3 - 5
                else _spriteAngleSnake.second.setRotation(270); // other case -> 2 - 6
                _spriteAngleSnake.second.setPosition(_scale * (currPos.x + 0.5), _scale * (currPos.y + 0.5));
                _window->draw(_spriteAngleSnake.second);
            }
        }

        // draw the tail
        sf::Vector2i &tailPos = snake.back();
        sf::Vector2i &beforeTailPos = snake[snake.size() - 2];
        if (tailPos.x < beforeTailPos.x) _spriteTailSnake.second.setRotation(180);
        else if (tailPos.x > beforeTailPos.x) _spriteTailSnake.second.setRotation(0);
        else if (tailPos.y < beforeTailPos.y) _spriteTailSnake.second.setRotation(270);
        else if (tailPos.y > beforeTailPos.y) _spriteTailSnake.second.setRotation(90);
        _spriteTailSnake.second.setPosition(_scale * (tailPos.x + 0.5), _scale * (tailPos.y + 0.5));
        _window->draw(_spriteTailSnake.second);
    }

    // draw the apple
    _spriteApple.second.setPosition(_scale * (_posApple.x + 0.5), _scale * (_posApple.y + 0.5));
    _window->draw(_spriteApple.second);
    _window->display();

}

void Game::_update() {
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            _window->close();
        }
        if (_event.type == sf::Event::KeyPressed) {
            switch (_event.key.code) {
                case sf::Keyboard::Escape:
                    _window->close();
                    break;
                case sf::Keyboard::Up:
                    std::cout << "UP" << std::endl;
                    break;
                case sf::Keyboard::Down:
                    std::cout << "DOWN" << std::endl;
                    break;
                case sf::Keyboard::Left:
                    std::cout << "LEFT" << std::endl;
                    break;
                case sf::Keyboard::Right:
                    std::cout << "RIGHT" << std::endl;
                    break;
                default:
                    break;
            }
        }
    }
}

void Game::_setSnake(uint id, std::vector<sf::Vector2i> snakePos) {
    if (id >= _posSnakes.size())
        _posSnakes.resize(id + 1);
    _posSnakes[id] = snakePos;
}

void Game::_setApple(sf::Vector2i applePos) {
    _posApple = applePos;
}

int Game::run() {
    _setup();

    while (_window->isOpen()) {
        _update();
        _draw();
    }
    return 0;
}

