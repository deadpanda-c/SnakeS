#ifndef CORE_HPP
#define CORE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>
#include <mutex>
#include <regex>

#include "Enum.hpp"

class Core
{
    public:
        Core();
        Core(sf::Vector2<int> windowSize, sf::Vector2<int> gameSize, std::pair<std::string, int> ipPort);
        ~Core();

        void setWindowSize(sf::Vector2<int> windowSize);
        void setGameSize(sf::Vector2<int> gameSize);
        int setIpPort(std::pair<std::string, unsigned short> ipPort);

        void run();
    
    private:
        void _setup();
        void _draw();
        void _update(); // Not defined yet
        void _setSnake(int id, std::vector<std::pair<int, int>> snakePos); // Not defined yet
        void _setApple(std::pair<int, int> applePos); // Not defined yet
        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _loadSprite(const std::string &path);
        
        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _sprite_middle_snake;
        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _sprite_head_snake;
        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _sprite_tail_snake;
        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _sprite_angle_snake;
        std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> _sprite_apple;


        sf::TcpSocket _socket;
        sf::RenderWindow _window;
        sf::Event _event;
        sf::Vector2<int> _windowSize;
        sf::Vector2<int> _gameSize;
        std::vector<std::vector<sf::Vector2i>> _pos_snakes;
        sf::Vector2i _pos_apple;
        float _scale;
};

#endif // CORE_HPP