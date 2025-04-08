#ifndef CLIENT_CONNECTION_MANAGER_HPP
#define CLIENT_CONNECTION_MANAGER_HPP
#include "Manager/SocketManager.hpp"
#include "Manager/MessageManager.hpp"
#include "NetworkInformation.hpp"

class ClientConnectionManager : public NetworkInformation {
public:
    ClientConnectionManager() {
        try {
            server_sock = SocketManager::createSocket();
        } catch (const std::runtime_error &e) {
            std::cerr << "Socket creation failed: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }

        if (inet_pton(AF_INET, IP, &address.sin_addr) <= 0) {
            std::cerr << "Invalid address" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (connect(server_sock, (struct sockaddr *)&address, sizeof(address)) < 0) {
            std::cerr << "Connection failed" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "Connected to server at " << IP << ":" << PORT << std::endl;
    }

    int getServerSocket() const { return server_sock; }

    ~ClientConnectionManager() {
        SocketManager::closeSocket(server_sock);
    }

private:
    int server_sock = -1;
};

#endif // CLIENT_CONNECTION_MANAGER_HPP