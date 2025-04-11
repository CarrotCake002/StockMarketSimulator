#include "Controllers/ServerConnectionController.hpp"
#include "Controllers/CommandController.hpp"

#include <iostream>
#include <string>
#include <thread>

bool inputErrorHandling(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <port>" << std::endl;
        return false;
    }
    if (std::stoi(av[1]) <= 0 || std::stoi(av[1]) > 65535) {
        std::cerr << ERROR_INVALID_PORT << std::endl;
        return false;
    }
    return true;
}

void handleConnectedClient(int client_socket) {
    CommandController commandController(client_socket);

    while (true) {
        try {
            std::string clientInput = Message::receiveMessage(client_socket);
            Command command = commandController.parseCommand(clientInput);

            commandController.executeCommand(command);
        } catch (const Exception::ClientDisconnected &e) {
            std::cerr << ERROR << e.what() << std::endl;
            Message::sendMessage(client_socket, ERROR_PROCESSING_COMMAND);
            break;
        } catch (const std::invalid_argument &e) {
            std::cerr << ERROR << e.what() << std::endl;
            Message::sendMessage(client_socket, ERROR_INVALID_COMMAND);
            continue;
        } catch (const std::runtime_error &e) {
            std::cerr << ERROR << e.what() << std::endl;
            Message::sendMessage(client_socket, ERROR_PROCESSING_COMMAND);
            continue;
        } catch (std::exception &e) {
            std::cerr << ERROR << e.what() << std::endl;
            Message::sendMessage(client_socket, ERROR_PROCESSING_COMMAND);
            continue;
        }
    }
    std::cout << "exited" << std::endl;
    SocketController::closeSocket(client_socket);
}

// Function to handle client connections
void handleClientConnections(int port) {
    try {
        ServerConnectionController server(port);

        server.listenForConnections();

        while (true) {
            int client_socket = server.acceptConnection();

            if (client_socket < 0) {
                std::cerr << ERROR_ACCEPTING << std::endl;
                continue;
            }
            std::thread client_thread(handleConnectedClient, client_socket);
            client_thread.detach(); // Detach the thread to handle multiple clients
            std::cout << INFO_CLIENT_CONNECTED_FD << client_socket << std::endl;
            std::cout << INFO_WAITING_NEW_CONNECTION << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << RUNTIME_ERROR << e.what() << std::endl;
        throw;
    } catch (...) {
        std::cerr << ERROR_UNEXPECTED << std::endl;
        throw;
    }
}

int main(int ac, char **av) {
    if (!inputErrorHandling(ac, av))
        return 84;
    int port = std::stoi(av[1]);

    try {
        handleClientConnections(port);
    } catch (...) {
        return 84;
    }

    return 0;
}
