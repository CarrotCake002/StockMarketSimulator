#include "ClientConnectionManager.hpp"

bool inputErrorHandling(int ac, char **av) {
    if (ac > 3) {
        std::cerr << "Usage: " << av[0] << " <IP> <PORT>" << std::endl;
        return true;
    }
    if (ac == 2 && std::string(av[1]).find_first_not_of("0123456789.") != std::string::npos) {
        std::cerr << "Invalid IP address format." << std::endl;
        return true;
    }
    if (ac == 3 && av[2]) {
        int port = std::stoi(av[2]);
        if (port < 0 || port > 65535) {
            std::cerr << "Port number must be between 0 and 65535." << std::endl;
            return true;
        }
    }
    return false;
}

int main(int ac, char **av) {
    if (inputErrorHandling(ac, av))
        return 84;
    std::string ip = av[1];
    int port = std::stoi(av[2]);
    ClientConnectionManager client(ip, port);

    std::string message = Message::receiveMessage(client.getClientSocket());
    std::cout << "Message from server: " << message << std::endl;
    Message::sendMessage(client.getClientSocket(), "Hello from client!");
    return 0;
}
