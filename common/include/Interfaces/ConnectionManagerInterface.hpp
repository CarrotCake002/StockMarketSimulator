#ifndef CONNECTION_MANAGER_INTERFACE_HPP
#define CONNECTION_MANAGER_INTERFACE_HPP

#include "NetworkInformation.hpp"

class ConnectionManagerInterface : public NetworkInformation{
public:
    virtual ~ConnectionManagerInterface() = default;

    virtual void createSocket() = 0;
    virtual void closeSocket(int socket) = 0;
};

#endif // CONNECTION_MANAGER_INTERFACE_HPP