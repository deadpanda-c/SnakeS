#include "Button.hpp"

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text, int textSize) {
    _button.setPosition(position);
    _button.setSize(size);
    _button.setFillColor(sf::Color::Black);
    _button.setOutlineColor(sf::Color::White);
    _button.setOutlineThickness(10);

    _font.loadFromFile(FONT);
    _buttonText.setFont(_font);
    _buttonText.setString(text);
    _buttonText.setCharacterSize(textSize);
    _buttonText.setFillColor(sf::Color::White);
    _buttonText.setPosition(position.x + size.x / 2 - _buttonText.getGlobalBounds().width / 2, position.y + size.y / 2 - _buttonText.getGlobalBounds().height / 2 - textSize / 2.7);
}

Button::~Button() {}

bool Button::update(sf::Vector2i mousePos, bool isClicking) {
    if (_button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        _button.setFillColor(sf::Color(64, 64, 64));
        if (isClicking) {
            return true;
        }
    } else {
        _button.setFillColor(sf::Color::Black);
    }

    return false;
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(_button);
    window.draw(_buttonText);
}



