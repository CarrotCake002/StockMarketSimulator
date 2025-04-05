#ifndef MESSAGE_MANAGER_HPP
#define MESSAGE_MANAGER_HPP

#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>

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
            return "";
        }
        return std::string(buffer, valread);
    }
};

#endif // MESSAGE_MANAGER_HPP