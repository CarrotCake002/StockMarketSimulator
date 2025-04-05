#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include "Manager/SocketManager.hpp"
#include "Manager/MessageManager.hpp"
#include "NetworkInformation.hpp"

class ConnectionManager : public NetworkInformation {
public:
    ConnectionManager(){
        try {
            client_sock = SocketManager::createSocket();
        } catch (const std::runtime_error &e) {
            std::cerr << "Socket creation failed: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }

        if (inet_pton(AF_INET, IP, &address.sin_addr) <= 0) {
            std::cerr << "Invalid address" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (connect(client_sock, (struct sockaddr *)&address, sizeof(address)) < 0) {
            std::cerr << "Connection failed" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "Connected to server at " << IP << ":" << PORT << std::endl;
    }

    int getClientSocket() const { return client_sock; }

    ~ConnectionManager() {
        SocketManager::closeSocket(client_sock);
    }

private:
    int client_sock = -1;
};

#endif // CONNECTION_MANAGER_HPP