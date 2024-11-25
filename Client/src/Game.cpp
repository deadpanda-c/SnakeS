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

std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> Game::_loadSprite(const std::string &path) {
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    sf::Sprite sprite;
    
    if (!texture->loadFromFile(path)) {
        std::cerr << "Failed to load texture from " << path << std::endl;
    }
    sprite.setTexture(*texture);
    sprite.setScale(_scale / SPRITE_SIZE, _scale / SPRITE_SIZE);
    sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
    return std::make_pair(texture, sprite);
}

void Game::setWindow(std::shared_ptr<sf::RenderWindow> window) {
    _window = window;
}

void Game::_setup() {
    _windowSize = _window->getSize();
    _scale = _windowSize.x / _gameSize.x;

    // load all the sprites and textures
    _sprite_middle_snake = _loadSprite(SNAKE_MIDDLE);
    _sprite_head_snake = _loadSprite(SNAKE_HEAD);
    _sprite_tail_snake = _loadSprite(SNAKE_TAIL);
    _sprite_angle_snake = _loadSprite(SNAKE_ANGLE);
    _sprite_apple = _loadSprite(APPLE);

    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 20; i++) {
            _setSnake(j * 20 + i, {
                {i, j * 3 + 1},
                {i, j * 3 + 2},
                {i, j * 3 + 3},
            });
        }
    }
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

    for (std::vector<sf::Vector2i> &snake : _pos_snakes) {
        if (snake.empty()) continue;

        // set the color of the snake depending on its id. the color will be a gradient from red to green to blue
        float hue = ((&snake - &_pos_snakes[0]) * 1.0f / (_pos_snakes.size() + 1)) + (1.0f / (_pos_snakes.size() + 1));
        auto colorTuple = HSVtoRGB(hue, 1, 1);
        sf::Color color(std::get<0>(colorTuple), std::get<1>(colorTuple), std::get<2>(colorTuple));

        _sprite_angle_snake.second.setColor(color);
        _sprite_middle_snake.second.setColor(color);
        _sprite_head_snake.second.setColor(color);
        _sprite_tail_snake.second.setColor(color);

        // draw the head
        sf::Vector2i &headPos = snake.front();
        sf::Vector2i &nextPos = snake[1];
        if (headPos.x < nextPos.x) _sprite_head_snake.second.setRotation(0);
        else if (headPos.x > nextPos.x) _sprite_head_snake.second.setRotation(180);
        else if (headPos.y < nextPos.y) _sprite_head_snake.second.setRotation(90);
        else if (headPos.y > nextPos.y) _sprite_head_snake.second.setRotation(270);
        _sprite_head_snake.second.setPosition(_scale * (headPos.x + 0.5), _scale * (headPos.y + 0.5));
        _window->draw(_sprite_head_snake.second);

        // draw the body
        for (size_t i = 1; i < snake.size() - 1; ++i) {
            sf::Vector2i &prevPos = snake[i - 1];
            sf::Vector2i &currPos = snake[i];
            sf::Vector2i &nextPos = snake[i + 1];

            if ((prevPos.x == currPos.x && currPos.x == nextPos.x) || 
                (prevPos.y == currPos.y && currPos.y == nextPos.y)) { // straight segment
                if (prevPos.x != currPos.x) _sprite_middle_snake.second.setRotation(0);
                else _sprite_middle_snake.second.setRotation(90);
                _sprite_middle_snake.second.setPosition(_scale * (currPos.x + 0.5), _scale * (currPos.y + 0.5));
                _window->draw(_sprite_middle_snake.second);
            } else { // angle segment
                if ((prevPos.x < currPos.x && currPos.y < nextPos.y) || (prevPos.y > currPos.y && currPos.x > nextPos.x)) _sprite_angle_snake.second.setRotation(180); // 1 - 7
                else if ((prevPos.x > currPos.x && currPos.y < nextPos.y) || (prevPos.y > currPos.y && currPos.x < nextPos.x)) _sprite_angle_snake.second.setRotation(90); // 4 - 8
                else if ((prevPos.x > currPos.x && currPos.y > nextPos.y) || (prevPos.y < currPos.y && currPos.x < nextPos.x)) _sprite_angle_snake.second.setRotation(0); // 3 - 5
                else _sprite_angle_snake.second.setRotation(270); // other case -> 2 - 6
                _sprite_angle_snake.second.setPosition(_scale * (currPos.x + 0.5), _scale * (currPos.y + 0.5));
                _window->draw(_sprite_angle_snake.second);
            }
        }

        // draw the tail
        sf::Vector2i &tailPos = snake.back();
        sf::Vector2i &beforeTailPos = snake[snake.size() - 2];
        if (tailPos.x < beforeTailPos.x) _sprite_tail_snake.second.setRotation(180);
        else if (tailPos.x > beforeTailPos.x) _sprite_tail_snake.second.setRotation(0);
        else if (tailPos.y < beforeTailPos.y) _sprite_tail_snake.second.setRotation(270);
        else if (tailPos.y > beforeTailPos.y) _sprite_tail_snake.second.setRotation(90);
        _sprite_tail_snake.second.setPosition(_scale * (tailPos.x + 0.5), _scale * (tailPos.y + 0.5));
        _window->draw(_sprite_tail_snake.second);
    }

    // draw the apple
    _sprite_apple.second.setPosition(_scale * (_pos_apple.x + 0.5), _scale * (_pos_apple.y + 0.5));
    _window->draw(_sprite_apple.second);
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
    if (id >= _pos_snakes.size())
        _pos_snakes.resize(id + 1);
    _pos_snakes[id] = snakePos;
}

void Game::run() {
    _setup();

    while (_window->isOpen()) {
        _update();
        _draw();
    }
}

