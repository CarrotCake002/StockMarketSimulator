#ifndef SERVER_MESSAGE_CONTROLLER_HPP
#define SERVER_MESSAGE_CONTROLLER_HPP

#include "Controller/MessageController.hpp"

class ServerMessage : public Message {
public:
    ServerMessage() = default;
    ~ServerMessage() = default;

    static void sendMessage(int socket, const std::string& message) {
        std::string newMessage = message + std::string(INPUT_LINE_RESET);
        if (send(socket, newMessage.c_str(), newMessage.length(), 0) < 0) {
            throw std::runtime_error(ERROR_SENDING);
        }
    }
};

#endif // SERVER_MESSAGE_CONTROLLER_HPP