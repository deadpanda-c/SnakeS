#include <iostream>
#include "Graphics.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Graphics graphics(sf::Vector2<int>(800, 600), sf::Vector2<int>(800, 600));
    return 0;
}