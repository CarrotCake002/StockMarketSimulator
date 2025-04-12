#ifndef SERVER_CONNECTION_CONTROLLER_HPP
#define SERVER_CONNECTION_CONTROLLER_HPP

#include "Controller/SocketController.hpp"
#include "Message.hpp"

#include <fcntl.h>

class ServerConnectionController : public NetworkInformation {
public:
    ServerConnectionController(int port) : NetworkInformation(port) {
        try {
            server_fd = SocketController::createSocket();
            bindSocket();
        } catch (const std::runtime_error& e) {
            std::cerr << ERROR << e.what() << std::endl;
            throw;
        } catch (...) {
            std::cerr << ERROR_UNEXPECTED << std::endl;
            throw;
        }
    }

    ~ServerConnectionController() {
        SocketController::closeSocket(server_fd);
    }

    void bindSocket() {
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
            SocketController::closeSocket(server_fd);
            throw std::runtime_error(ERROR_SOCKET_BINDING);
        }
    }

    void listenForConnections() {
        if (listen(server_fd, 1) < 0) {
            throw std::runtime_error(ERROR_LISTENING);
        }
        std::cout << INFO_WAITING_FOR_CONNECTION << port << "..." << std::endl;
    }

    int acceptConnection() {
        int addrlen = sizeof(address);
        int flags = fcntl(server_fd, F_GETFL, 0);
        fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);

        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            return SOCKET_ERROR;
        }
        return client_socket;
    }

    int getClientSocket() const { return client_socket; }
    int getServerSocket() const { return server_fd; }

private:
    int server_fd = -1;
    int client_socket = -1;
};

#endif // SERVER_CONNECTION_CONTROLLER_HPP