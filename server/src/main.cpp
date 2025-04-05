#include "ConnectionManager.hpp"

int main() {
    int new_socket;

    try {
        ConnectionManager connectionManager;
        
        connectionManager.listenForConnections();
        new_socket = connectionManager.acceptConnection();

        std::string hello = "Hello from server";
        send(new_socket, hello.c_str(), hello.length(), 0);
        std::cout << "Message sent to client" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "An unexpected error occurred." << std::endl;
        return 84;
    }
    return 0;
}
