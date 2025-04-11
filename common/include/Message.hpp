#ifndef MESSAGE_CONTROLLER_HPP
#define MESSAGE_CONTROLLER_HPP

#include "Exception/ClientDisconnected.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

using Exception::ClientDisconnected;

class Message {
public:
    Message() = default;
    ~Message() = default;

    static void sendMessage(int socket, const std::string& message) {
        send(socket, message.c_str(), message.length(), 0);
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