#ifndef SERVER_CONNECTION_MANAGER_HPP
#define SERVER_CONNECTION_MANAGER_HPP

#include "Manager/SocketManager.hpp"
#include "Manager/MessageManager.hpp"
#include "NetworkInformation.hpp"

class ServerConnectionManager : public NetworkInformation {
public:
    ServerConnectionManager(int port) : NetworkInformation(port) {
        try {
            server_fd = SocketManager::createSocket();
            bindSocket();
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            throw;
        } catch (...) {
            std::cerr << "An unexpected error occurred." << std::endl;
            throw;
        }
    }

    ~ServerConnectionManager() {
        SocketManager::closeSocket(client_socket);
        SocketManager::closeSocket(server_fd);
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
    int server_fd = -1;
    int client_socket = -1;
};

#endif // SERVER_CONNECTION_MANAGER_HPP