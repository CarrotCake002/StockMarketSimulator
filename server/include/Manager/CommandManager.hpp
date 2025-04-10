#ifndef COMMAND_MANAGER_HPP
#define COMMAND_MANAGER_HPP

#include "Constants.hpp"

enum class Command {
    HELP,
    EXIT,
    LIST,
    SHUTDOWN
};

class CommandManager {
public:
    CommandManager(int client_socket) : client_socket(client_socket) {}
    ~CommandManager() = default;

    static Command parseCommand(const std::string& command) {
        if (command == "help") {
            return Command::HELP;
        } else if (command == "exit") {
            return Command::EXIT;
        } else if (command == "list") {
            return Command::LIST;
        } else if (command == "shutdown") {
            return Command::SHUTDOWN;
        } else {
            throw std::invalid_argument("Unknown command");
        }
    }

    void executeHelp(void) {
        std::cout << "Available commands:" << std::endl;
        std::cout << "  help      - Show this help message" << std::endl;
        std::cout << "  exit      - Exit the program" << std::endl;
        std::cout << "  list      - List all available stocks" << std::endl;
        std::cout << "  shutdown  - Shutdown the server" << std::endl;
    }

    void executeExit(void) {
        Message::sendMessage(client_socket, INFO_CLIENT_DISCONNECTED);
        std::cout << "Client with fd " << client_socket << " disconnected." << std::endl;
        SocketManager::closeSocket(client_socket);
    }

    void executeCommand(Command cmd) {
        if (cmd == Command::HELP) {
            executeHelp();
        } else if (cmd == Command::EXIT) {
            executeExit();
        } else if (cmd == Command::LIST) {
            // Handle list command
        } else if (cmd == Command::SHUTDOWN) {
            // Handle shutdown command
        } else {
            throw std::invalid_argument("Unknown command");
        }
    }

private:
    int client_socket;
};

#endif // COMMAND_MANAGER_HPP