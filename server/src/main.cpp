#include "ConnectionManager.hpp"
#include "Manager/MessageManager.hpp"

#include <iostream>
#include <string>

// Constants
const std::string SERVER_GREETING = "Hello from server";

// Function to handle client connections
void handleClientConnections() {
    int client_socket;

    try {
        ConnectionManager connectionManager;

        connectionManager.listenForConnections();
        client_socket = connectionManager.acceptConnection();
        Message::sendMessage(client_socket, SERVER_GREETING);
        std::cout << "Message from client: " << Message::receiveMessage(client_socket) << std::endl;
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
