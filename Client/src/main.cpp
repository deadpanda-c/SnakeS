#include "Core.hpp"

std::pair<std::string, unsigned short> parseArguments(int argc, char **argv) {
    // Check if the user wants to see the help message
    if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
    std::cout << "Usages:\n"
              << "  " << argv[0] << " -h | --help\n"
              << "  " << argv[0] << " <ip> <port>\n\n"
              << "Arguments:\n"
              << "  -h, --help    Show this help message and exit\n"
              << "  <ip>          Specify the IP address to connect to\n"
              << "  <port>        Specify the port number to use for the connection\n\n"
              << "Example:\n"
              << "  " << argv[0] << " 192.168.1.1 8080\n";
        return std::make_pair("__EXIT__", 0);
    }

    // Check if the user provided the correct number of arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " -h" << std::endl;
        return std::make_pair("__EXIT__", 1);
    }

    // Check if the IP address is valid
    std::regex ipRegex("^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)(\\.(?!$)|$)){4}$");

    if (!std::regex_match(argv[1], ipRegex)) {
        std::cerr << "Invalid ip address, expected format: x.x.x.x with x in [0, 255]" << std::endl;
        return std::make_pair("__EXIT__", 1);
    }

    // Check if the port number is valid
    try {
        int port = std::stoi(argv[2]);
        if (port < 0 || port > 65535) throw std::invalid_argument("Invalid port");
    } catch (std::invalid_argument &e) {
        std::cerr << "Invalid port, expected a number between 0 and 65535" << std::endl;
        return std::make_pair("__EXIT__", 1);
    }

    return std::make_pair(argv[1], std::stoi(argv[2]));
}

int main(int argc, char **argv) {
    std::pair<std::string, unsigned short> ipPort = parseArguments(argc, argv);
    Core core;

    if (ipPort.first == "__EXIT__") return ipPort.second;
    if (core.setIpPort(ipPort)) return 1; // Failed to connect to the server
    core.setGameSize(sf::Vector2<int>(20, 20));
    core.setWindowSize(sf::Vector2<int>(800, 800));
    core.run();
    return 0;
}