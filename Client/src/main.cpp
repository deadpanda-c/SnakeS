#include "Core.hpp"

int main(int argc, char **argv) {
    std::pair<std::string, unsigned short> ipPort = parseArguments(argc, argv);
    Core core;

    if (ipPort.first == "__EXIT__") return ipPort.second;
    // if (core.setIpPort(ipPort)) return 1; // Failed to connect to the server
    core.setGameSize(sf::Vector2<int>(20, 20));
    core.setWindowSize(sf::Vector2<int>(1600, 1600));
    core.run();
    return 0;
}