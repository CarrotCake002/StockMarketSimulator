#ifndef NETWORK_INFORMATION_HPP
#define NETWORK_INFORMATION_HPP

#include "Constants.hpp"

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <iostream>
#include <unistd.h>

class NetworkInformation {
public:
    NetworkInformation(int inputPort = SERVER_PORT, std::string ip = SERVER_IP) : port(inputPort), ipAddress(ip) {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
    }

    const sockaddr_in getAddress() const { return address; }
    std::string getIP() const { return ipAddress; }
    int getPort() const { return port; }

protected:
    int port;
    std::string ipAddress;
    struct sockaddr_in address;
};

#endif // NETWORK_INFORMATION_HPP