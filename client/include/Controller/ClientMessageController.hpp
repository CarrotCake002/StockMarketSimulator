#ifndef CLIENT_MESSAGE_CONTROLLER_HPP
#define CLIENT_MESSAGE_CONTROLLER_HPP

#include "Controller/MessageController.hpp"

class ClientMessage : public Message {
public:
    ClientMessage() = default;
    ~ClientMessage() = default;
};

#endif // CLIENT_MESSAGE_CONTROLLER_HPP