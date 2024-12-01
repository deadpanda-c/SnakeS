#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>
#include <mutex>
#include <regex>

#include "Constants.hpp"
#include "Tools.hpp"

class Game
{
    public:
        Game();
        ~Game();

        void setWindow(std::shared_ptr<sf::RenderWindow> window);
        void setGameSize(sf::Vector2<uint> gameSize);
        void setSocket(std::shared_ptr<sf::TcpSocket> socket);
        void setIpPort(std::shared_ptr<std::pair<std::string, ushort>> ipPort);
        int run();
    
    private:
        void _setup();
        void _draw();
        void _update();
        void _setSnake(uint id, std::vector<sf::Vector2i> snakePos);
        void _setApple(sf::Vector2i applePos); // Not defined yet
        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _loadSprite(const std::string &path);

        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _sprite_middle_snake;
        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _sprite_head_snake;
        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _sprite_tail_snake;
        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _sprite_angle_snake;
        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _sprite_apple;

        std::shared_ptr<sf::TcpSocket> _socket;
        std::shared_ptr<std::pair<std::string, ushort>> _ipPort;
        std::shared_ptr<sf::RenderWindow> _window;
        sf::Event _event;
        sf::Vector2<uint> _windowSize;
        sf::Vector2<uint> _gameSize;
        std::vector<std::vector<sf::Vector2i>> _pos_snakes;
        sf::Vector2i _pos_apple;
        float _scale;
};

#endif // GAME_HPP