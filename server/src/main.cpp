#include "ServerConnectionManager.hpp"
#include "Manager/MessageManager.hpp"

#include <iostream>
#include <string>
#include <thread>

const std::string SERVER_GREETING = "Hello from server";

void handleConnectedClient(int client_socket) {
    Message::sendMessage(client_socket, SERVER_GREETING);
    std::cout << "Message from client: " << Message::receiveMessage(client_socket) << std::endl;
    SocketManager::closeSocket(client_socket);
    std::cout << "Client with fd: " << client_socket << " disconnected." << std::endl;
}

// Function to handle client connections
void handleClientConnections() {
    try {
        ServerConnectionManager server;

        server.listenForConnections();

        while (true) {
            int client_socket = server.acceptConnection();

            if (client_socket < 0) {
                std::cerr << "Failed to accept connection." << std::endl;
                continue;
            }
            std::thread client_thread(handleConnectedClient, client_socket);
            client_thread.detach(); // Detach the thread to handle multiple clients
            std::cout << "Client connected with fd: " << client_socket << std::endl;
            std::cout << "Waiting for a new connection..." << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime Error: " << e.what() << std::endl;
        throw;
    } catch (...) {
        std::cerr << "An unexpected error occurred." << std::endl;
        throw;
    }
}

int main() {
    try {
        handleClientConnections();
    } catch (...) {
        return 84;
    }

    return 0;
}
