#ifndef SERVER_MESSAGE_CONTROLLER_HPP
#define SERVER_MESSAGE_CONTROLLER_HPP

#include "Controller/MessageController.hpp"

class ServerMessage : public Message {
public:
    ServerMessage() = default;
    ~ServerMessage() = default;
};

#endif // SERVER_MESSAGE_CONTROLLER_HPP