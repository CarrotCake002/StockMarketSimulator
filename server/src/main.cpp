#include "Controller/ServerConnectionController.hpp"
#include "Controller/CommandController.hpp"
#include "Atomic.hpp"

#include <iostream>
#include <string>
#include <thread>

std::atomic<bool> serverShutdown(false);

// Error handling
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

// Function to handle client commands in a separate thread
void handleConnectedClient(int client_socket) {
    CommandController commandController(client_socket);

    while (!serverShutdown) {
        try {
            std::string clientInput = ServerMessage::receiveMessage(client_socket);
            Command command = commandController.parseCommand(clientInput);

            commandController.executeCommand(command);
        } catch (const Exception::ClientDisconnected &e) {
            std::cerr << ERROR << e.what() << std::endl;
            ServerMessage::sendMessage(client_socket, ERROR_PROCESSING_COMMAND);
            break;
        } catch (const std::invalid_argument &e) {
            std::cerr << ERROR << e.what() << std::endl;
            ServerMessage::sendMessage(client_socket, ERROR_INVALID_COMMAND);
            continue;
        } catch (const std::runtime_error &e) {
            std::cerr << ERROR << e.what() << std::endl;
            ServerMessage::sendMessage(client_socket, ERROR_PROCESSING_COMMAND);
            continue;
        } catch (std::exception &e) {
            std::cerr << ERROR << e.what() << std::endl;
            ServerMessage::sendMessage(client_socket, ERROR_PROCESSING_COMMAND);
            continue;
        }
    }
    SocketController::closeSocket(client_socket);
}

// Function to handle client connections
void handleClientConnections(int port) {
    try {
        ServerConnectionController server(port);

        server.listenForConnections();

        while (!serverShutdown) {
            int client_socket = server.acceptConnection();

            if (client_socket < 0)
                continue;
            std::thread client_thread(handleConnectedClient, client_socket);
            client_thread.detach();
            std::cout << INFO_CLIENT_CONNECTED_FD << client_socket << std::endl;
        }
        SocketController::closeSocket(server.getServerSocket());
    } catch (const std::runtime_error& e) {
        throw;
    } catch (...) {
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
