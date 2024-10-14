#include "Graphics.hpp"

Graphics::Graphics(sf::Vector2<int> windowSize, sf::Vector2<int> gameSize): windowSize(windowSize), gameSize(gameSize) {
    window.create(sf::VideoMode(windowSize.x, windowSize.y), "Game");
    window.setFramerateLimit(60);
}

Graphics::~Graphics() {
    window.close();
}