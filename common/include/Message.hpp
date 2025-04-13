#ifndef MESSAGE_CONTROLLER_HPP
#define MESSAGE_CONTROLLER_HPP

#include "Exception/ClientDisconnected.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

class Message {
public:
    Message() = default;
    ~Message() = default;

    static void sendMessage(int socket, const std::string& message) {
        if (send(socket, message.c_str(), message.length(), 0) < 0) {
            throw std::runtime_error(ERROR_SENDING);
        }
    }

    static std::string receiveMessage(int socket) {
        char buffer[1024] = {0};
        int valread = read(socket, buffer, 1024);

        if (valread < 0) {
            throw std::runtime_error(ERROR_READING_SOCKET);
        } else if (valread == 0) {
            throw Exception::ClientDisconnected(socket);
        }
        return std::string(buffer, valread);
    }
};

#endif // MESSAGE_CONTROLLER_HPP