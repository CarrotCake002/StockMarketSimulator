#ifndef NETWORK_INFORMATION_HPP
#define NETWORK_INFORMATION_HPP

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <iostream>
#include <unistd.h>


#define PORT 8080
#define IP "127.0.0.1"

class NetworkInformation {
public:
    NetworkInformation(void) {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);
    }

    const sockaddr_in getAddress() const { return address; }
    std::string getIP() const { return ipAddress; }
    int getPort() const { return port; }

protected:
    int port = 8080;
    std::string ipAddress = IP;
    struct sockaddr_in address;
};

#endif // NETWORK_INFORMATION_HPP