#ifndef MESSAGE_MANAGER_HPP
#define MESSAGE_MANAGER_HPP

#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <system_error>

#include "Constants.hpp"

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
            throw std::system_error(errno, std::system_category(), ERROR_CONNECTION_CLOSED);
        }
        return std::string(buffer, valread);
    }
};

#endif // MESSAGE_MANAGER_HPP