#ifndef SERVER_INFORMATION_HPP
#define SERVER_INFORMATION_HPP

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <iostream>
#include <unistd.h>


#define PORT 8080
#define IP "127.0.0.1"

class NetworkInformation {
protected:
    int port;
    std::string ipAddress;
    struct sockaddr_in address;

public:
    NetworkInformation(void) : ipAddress(IP), port(PORT) {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
    }

    const sockaddr_in& getAddress() const { return address; }
    std::string getIP() const { return ipAddress; }
    int getPort() const { return port; }
};

#endif // SERVER_INFORMATION_HPP