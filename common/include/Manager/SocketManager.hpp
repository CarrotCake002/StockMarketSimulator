#ifndef SOCKET_MANAGER_HPP
#define SOCKET_MANAGER_HPP

#include "NetworkInformation.hpp"

class SocketManager {
public:
    virtual ~SocketManager() = default;

    static int createSocket() {
        int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

        if (socket_fd < 0) {
            throw std::runtime_error(ERROR_SOCKET_CREATION);
        }
        return socket_fd;
    }

    static void closeSocket(int socket) {
        if (socket >= 0) {
            close(socket);
        } else {
            std::cerr << ERROR_INVALID_SOCKET << std::endl;
        }
    }
};

#endif // SOCKET_MANAGER_HPP