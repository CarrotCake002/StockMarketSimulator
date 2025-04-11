#ifndef COMMAND_CONTROLLER_HPP
#define COMMAND_CONTROLLER_HPP

#include "Constants.hpp"
#include "Controller/SocketController.hpp"
#include "Exception/ServerDisconnected.hpp"
#include "Message.hpp"

enum class Command {
    HELP,
    EXIT,
    LIST,
    SHUTDOWN
};

class CommandController {
public:
    CommandController(int client_socket) : client_socket(client_socket) {}
    ~CommandController() = default;

    Command parseCommand(const std::string& command) {
        std::cout << "\"" << command << "\" received from client with fd " << client_socket << std::endl;
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
        const std::string helpMessage =
        "Available commands:\n"
        "  help      - Show this help message\n"
        "  exit      - Exit the program\n"
        "  list      - List all available stocks\n"
        "  shutdown  - Shutdown the server\n";
        Message::sendMessage(client_socket, helpMessage);
        std::cout << "Help message sent to client with fd " << client_socket << std::endl;
    }

    void executeExit(void) {
        Message::sendMessage(client_socket, INFO_CLIENT_DISCONNECTED);
        std::cout << "Client with fd " << client_socket << " disconnected." << std::endl;
        SocketController::closeSocket(client_socket);
    }

    void executeShutdown(void) {
        Message::sendMessage(client_socket, INFO_SERVER_SHUTDOWN);
        std::cout << INFO_SERVER_SHUTDOWN << std::endl;
        SocketController::closeSocket(client_socket);
    }

    void executeCommand(Command cmd) {
        if (cmd == Command::HELP) {
            executeHelp();
        } else if (cmd == Command::EXIT) {
            executeExit();
        } else if (cmd == Command::LIST) {
            // Handle list command
        } else if (cmd == Command::SHUTDOWN) {
            executeShutdown();
            throw Exception::ServerDisconnected(client_socket);
        } else {
            throw std::invalid_argument("Unknown command");
        }
    }

private:
    int client_socket;
};

#endif // COMMAND_CONTROLLER_HPP