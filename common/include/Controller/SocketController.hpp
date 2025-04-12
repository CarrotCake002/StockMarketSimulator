#ifndef SOCKET_fd_CONTROLLER_HPP
#define SOCKET_fd_CONTROLLER_HPP

#include "NetworkInformation.hpp"

class Socket_fdController {
public:
    virtual ~Socket_fdController() = default;

    static int createSocket_fd() {
        int socket_fd_fd = socket(AF_INET, SOCK_STREAM, 0);

        if (socket_fd_fd < 0) {
            throw std::runtime_error(ERROR_SOCKET_CREATION);
        }
        return socket_fd_fd;
    }

    static void closeSocket_fd(int socket_fd) {
        if (socket_fd >= 0) {
            close(socket_fd);
        } else {
            throw std::runtime_error(ERROR_SOCKET_CLOSING);
        }
    }
};

#endif // SOCKET_fd_CONTROLLER_HPP