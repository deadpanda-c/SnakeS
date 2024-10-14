#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <mutex>

class Graphics
{
    public:
        Graphics(sf::Vector2<int> windowSize, sf::Vector2<int> gameSize);
        ~Graphics();
    
    private:
        sf::RenderWindow window;
        sf::Event event;
        const sf::Vector2<int> windowSize;
        const sf::Vector2<int> gameSize;

        std::mutex mapLock;
        std::vector<int> *map;

};

#endif // GRAPHICS_HPP