#include "Tools.hpp"

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

std::tuple<int, int, int> HSVtoRGB(float h, float s, float v) {
    int r, g, b;

    int i = static_cast<int>(h * 6);
    float f = h * 6 - i;
    int p = static_cast<int>(v * (1 - s) * 255);
    int q = static_cast<int>(v * (1 - f * s) * 255);
    int t = static_cast<int>(v * (1 - (1 - f) * s) * 255);

    switch (i % 6) {
        case 0: r = v * 255; g = t; b = p; break;
        case 1: r = q; g = v * 255; b = p; break;
        case 2: r = p; g = v * 255; b = t; break;
        case 3: r = p; g = q; b = v * 255; break;
        case 4: r = t; g = p; b = v * 255; break;
        case 5: r = v * 255; g = p; b = q; break;
    }

    return std::make_tuple(r, g, b);
}