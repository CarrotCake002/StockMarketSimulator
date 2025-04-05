#ifndef COMMUNICATION_MANAGER_HPP
#define COMMUNICATION_MANAGER_HPP

#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>

class CommunicationManager {
public:
    CommunicationManager() = default;
    ~CommunicationManager() = default;

    static void sendMessage(int socket, const std::string& message) {
        send(socket, message.c_str(), message.length(), 0);
    }

    static std::string receiveMessage(int socket) {
        char buffer[1024] = {0};
        int valread = read(socket, buffer, 1024);
        return std::string(buffer, valread);
    }
};

#endif // COMMUNICATION_MANAGER_HPP