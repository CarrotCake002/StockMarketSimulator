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

void handleConnection(std::string ip, int port) {
    ClientConnectionManager client(ip, port);
    std::string clientCommand;
    std::string serverResponse;

    while (true) {
        std::getline(std::cin, clientCommand);
        Message::sendMessage(client.getServerSocket(), clientCommand);
        serverResponse = Message::receiveMessage(client.getServerSocket());
        std::cout << "Response from server: " << serverResponse << std::endl;
    }
}

int main(int ac, char **av) {
    if (inputErrorHandling(ac, av))
        return 84;
    try {
    handleConnection(std::string(av[1]), std::stoi(av[2]));
    } catch (const std::runtime_error &e) {
        std::cerr << "Runtime Error: " << e.what() << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "An unexpected error occurred." << std::endl;
        return 84;
    }
    return 0;
}
