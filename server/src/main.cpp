#include "ServerConnectionManager.hpp"
#include "Manager/MessageManager.hpp"
#include "Input.hpp"

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
    while (true) {
        try {
            auto clientCommand = Message::receiveMessage(client_socket);
    
            std::cout << "\"" << clientCommand << "\" received from client with fd " << client_socket << std::endl;
            Input::validate(clientCommand);
            if (Input::checkExit(clientCommand)) {
                Message::sendMessage(client_socket, INFO_CLIENT_DISCONNECTED);
                std::cout << "Client with fd "<< client_socket << "disconnected." << std::endl;
                break;
            } else if (Input::checkHelp(clientCommand)) {
                Message::sendMessage(client_socket, HELP_MESSAGE);
                continue;
            } else {
                Message::sendMessage(client_socket, ERROR_UNKNOWN_COMMAND);
                throw std::invalid_argument(ERROR_UNKNOWN_COMMAND);
            }
        } catch (const std::system_error &e) {
            std::cerr << ERROR << e.what() << std::endl;
            Message::sendMessage(client_socket, ERROR_PROCESSING_COMMAND);
            std::cout << "Client with fd " << client_socket << "disconnected." << std::endl;
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
    SocketManager::closeSocket(client_socket);
}

// Function to handle client connections
void handleClientConnections(int port) {
    try {
        ServerConnectionManager server(port);

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
