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
    _windowSize = windowSize;
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

std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> Core::_loadSprite(const std::string &path) {
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

void Core::_setup() {
    if (!_windowSize.x || !_windowSize.y || !_gameSize.x || !_gameSize.y) {
        std::cerr << "Window size and game size must be set before running the game" << std::endl;
        return;
    }
    
    _scale = _windowSize.x / _gameSize.x;
    _window.create(sf::VideoMode(_windowSize.x, _windowSize.y), "SnakeS");
    _window.setFramerateLimit(60);

    // load all the sprites and textures
    _sprite_middle_snake = _loadSprite(SNAKE_MIDDLE);
    _sprite_head_snake = _loadSprite(SNAKE_HEAD);
    _sprite_tail_snake = _loadSprite(SNAKE_TAIL);
    _sprite_angle_snake = _loadSprite(SNAKE_ANGLE);
    _sprite_apple = _loadSprite(APPLE);

    // All of the code below is for testing purposes
    //
    //    S--1 4-1
    //       | | |
    // 8---7 2-3 |
    // |   |     |
    // | 4-3     |
    // | 6-------5
    // E
    //
    // SAME ANGLES:
    // 1 - 7 // 180
    // 2 - 6 // 0
    // 3 - 5 // 270
    // 4 - 8 // 90

    std::vector<sf::Vector2i> snake = {
        {4, 0},  // S
        {5, 0},  // -
        {6, 0},  // -
        {7, 0},  // 1
        {7, 1},  // |
        {7, 2},  // 2
        {8, 2},  // -
        {9, 2},  // 3
        {9, 1},  // |
        {9, 0},  // 4
        {10, 0}, // -
        {11, 0}, // 1
        {11, 1}, // |
        {11, 2}, // |
        {11, 3}, // |
        {11, 4}, // |
        {11, 5}, // 5
        {10, 5}, // -
        {9, 5},  // -
        {8, 5},  // -
        {7, 5},  // -
        {6, 5},  // -
        {5, 5},  // -
        {4, 5},  // -
        {3, 5},  // 6
        {3, 4},  // 4
        {4, 4},  // -
        {5, 4},  // 3
        {5, 3},  // |
        {5, 2},  // 7
        {4, 2},  // -
        {3, 2},  // -
        {2, 2},  // -
        {1, 2},  // 8
        {1, 3},  // |
        {1, 4},  // |
        {1, 5},  // |
        {1, 6},  // E

    };
    _pos_snakes.push_back(snake);
    for (int i = 0; i < 20; i++) {
        _pos_snakes.push_back({
            {12, i},
            {13, i},
            {14, i}
        });
    }
    for (int i = 0; i < 20; i++) {
        _pos_snakes.push_back({
            {15, i},
            {16, i},
            {17, i}
        });
    }
}

void Core::_draw() { // todo: handle of the snake is shorter than 3
    // draw the grid for debug purposes
    for (int i = 0; i <= _gameSize.x; i++) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(i * _scale, 0)),
            sf::Vertex(sf::Vector2f(i * _scale, _windowSize.y))
        };
        line[0].color = sf::Color(255, 255, 255, 64);
        line[1].color = sf::Color(255, 255, 255, 64);
        _window.draw(line, 2, sf::Lines);
    }
    for (int i = 0; i <= _gameSize.y; i++) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, i * _scale)),
            sf::Vertex(sf::Vector2f(_windowSize.x, i * _scale))
        };
        line[0].color = sf::Color(255, 255, 255, 64);
        line[1].color = sf::Color(255, 255, 255, 64);
        _window.draw(line, 2, sf::Lines);
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
        _window.draw(_sprite_head_snake.second);

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
                _window.draw(_sprite_middle_snake.second);
            } else { // angle segment
                if ((prevPos.x < currPos.x && currPos.y < nextPos.y) || (prevPos.y > currPos.y && currPos.x > nextPos.x)) _sprite_angle_snake.second.setRotation(180); // 1 - 7
                else if ((prevPos.x > currPos.x && currPos.y < nextPos.y) || (prevPos.y > currPos.y && currPos.x < nextPos.x)) _sprite_angle_snake.second.setRotation(90); // 4 - 8
                else if ((prevPos.x > currPos.x && currPos.y > nextPos.y) || (prevPos.y < currPos.y && currPos.x < nextPos.x)) _sprite_angle_snake.second.setRotation(0); // 3 - 5
                else _sprite_angle_snake.second.setRotation(270); // other case -> 2 - 6
                _sprite_angle_snake.second.setPosition(_scale * (currPos.x + 0.5), _scale * (currPos.y + 0.5));
                _window.draw(_sprite_angle_snake.second);
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
        _window.draw(_sprite_tail_snake.second);
    }

    // draw the apple
    _sprite_apple.second.setPosition(_scale * (_pos_apple.x + 0.5), _scale * (_pos_apple.y + 0.5));
    _window.draw(_sprite_apple.second);
}

       




void Core::run() {
    _setup();

    while (_window.isOpen()) {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                _window.close();
            }
        }

        _window.clear();
        _draw();
        _window.display();
    }
}

