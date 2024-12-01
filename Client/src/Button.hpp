#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Constants.hpp"

class Button {
    public:
        Button(sf::Vector2f position, sf::Vector2f size, std::string text, int textSize);
        ~Button();

        bool update(sf::Vector2i mousePos, bool isClicking);
        void draw(sf::RenderWindow &window);
    private:

        sf::RectangleShape _button;
        sf::Text _buttonText;
        sf::Font _font;
};

#endif // BUTTON_HPP