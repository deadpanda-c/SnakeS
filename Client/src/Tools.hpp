#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <SFML/Graphics.hpp>

#include <tuple>
#include <iostream>
#include <regex>

#include "Constants.hpp"

namespace Tools
{
    std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> loadSprite(const std::string &path, float scale);

    /*
    Processes the arguments passed to the program
    -- If the user wants to see the help message, it will display it and return a pair containing "__EXIT__" and 0
    -- Else, it will check if the IP address and the port number are valid and return them as a pair
    -- if the IP address or the port number are invalid, it will display an error message and return a pair containing "__EXIT__" and 1

    @param argc: The number of arguments
    @param argv: The arguments

    @return: A pair containing the IP address and the port number
    */
    std::pair<std::string, ushort> parseArguments(int argc, char **argv);

    /*
    // Converts HSV color to RGB

    @param h: The hue
    @param s: The saturation
    @param v: The value

    @returns: A tuple containing the RGB values

    PS: This function was made by ChatGPT
    */
    std::tuple<int, int, int> HSVtoRGB(float h, float s, float v);
}


#endif // TOOLS_HPP