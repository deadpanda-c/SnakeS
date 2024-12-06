#include "Core.hpp"

int main(int argc, char **argv) {
    std::pair<std::string, ushort> ipPort = Tools::parseArguments(argc, argv);
    Core core;

    if (ipPort.first == "__EXIT__")
        return ipPort.second;
    core.setIpPort(ipPort);
    core.setWindowSize(800);
    core.setGameSize(20);
    return core.run();
}