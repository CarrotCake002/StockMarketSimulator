#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include "NetworkInformation.hpp"

class ConnectionManager : public NetworkInformation {
public:
    ConnectionManager() {
        try {
            createSocket();
            bindSocket();
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            throw;
        } catch (...) {
            std::cerr << "An unexpected error occurred." << std::endl;
            throw;
        }
    }

    ~ConnectionManager() {
        // Destructor implementation
        try {
            close(client_socket);
            close(server_fd);
        } catch (...) {
            std::cerr << "Error closing sockets" << std::endl;
        }
    }

    void createSocket() {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == 0) {
            throw std::runtime_error("Socket failed");
        }
    }

    void bindSocket() {
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
            throw std::runtime_error("Bind failed");
        }
    }

    void listenForConnections() {
        if (listen(server_fd, 1) < 0) {
            throw std::runtime_error("Listen failed");
        }
        std::cout << "Waiting for a connection on port " << port << "...\n";
    }

    int acceptConnection() {
        int addrlen = sizeof(address);

        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            throw std::runtime_error("Accept failed");
        }
        return client_socket;
    }

    int getClientSocket() const { return client_socket; }

private:
    int server_fd;
    int client_socket;
};

#endif // CONNECTION_MANAGER_HPP