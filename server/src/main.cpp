#include "ConnectionManager.hpp"
#include "CommunicationManager.hpp"

#include <iostream>
#include <string>

// Constants
const std::string SERVER_GREETING = "Hello from server";

// Function to handle client connections
void handleClientConnections() {
    int new_socket;

    try {
        ConnectionManager connectionManager;

        connectionManager.listenForConnections();
        new_socket = connectionManager.acceptConnection();
        CommunicationManager::sendMessage(new_socket, SERVER_GREETING);
        std::cout << "Message sent to client" << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime Error: " << e.what() << std::endl;
        throw; // Re-throw the exception for further handling if needed
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
