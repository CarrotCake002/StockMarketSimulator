#include "Controllers/ClientConnectionController.hpp"
#include "Signals.hpp"

bool inputErrorHandling(int ac, char **av) {
    if (ac > 3) {
        std::cerr << "Usage: " << av[0] << " <IP> <PORT>" << std::endl;
        return true;
    }
    if (ac == 2 && std::string(av[1]).find_first_not_of(IP_FORMAT) != std::string::npos) {
        std::cerr << ERROR_INVALID_IP << std::endl;
        return true;
    }
    if (ac == 3 && av[2]) {
        int port = std::stoi(av[2]);
        if (port < PORT_MIN || port > PORT_MAX) {
            std::cerr << ERROR_INVALID_PORT << std::endl;
            return true;
        }
    }
    return false;
}

bool checkExitCommand(std::string command) {
    return shouldExit || command == EXIT_COMMAND;
}

void handleInput() {
    
}

void handleConnection(std::string ip, int port) {
    ClientConnectionController client(ip, port);
    std::string clientInput;
    std::string serverResponse;

    while (true) {
        try {
            std::cout << INPUT_PROMPT;
            std::getline(std::cin, clientInput);
            if (clientInput.empty()) {
                std::cerr << ERROR << ERROR_INVALID_COMMAND << std::endl;
                continue;
            }
            if (checkExitCommand(clientInput)) {
                std::cout << INFO_EXITING_CLIENT << std::endl;
                break;
            }
            Message::sendMessage(client.getServerSocket(), clientInput);
            serverResponse = Message::receiveMessage(client.getServerSocket());
            std::cout << RESPONSE << serverResponse << std::endl;
        } catch (const std::runtime_error &e) {
            std::cerr << ERROR << e.what() << std::endl;
            break;
        } catch (...) {
            std::cerr << ERROR_UNEXPECTED << std::endl;
            throw;
        }
    }
}

int main(int ac, char **av) {
    signal(SIGINT, signalHandler);
    if (inputErrorHandling(ac, av))
        return 84;
    try {
        handleConnection(std::string(av[1]), std::stoi(av[2]));
    } catch (...) {
        return 84;
    }
    return 0;
}
