#ifndef CLIENT_CONNECTION_CONTROLLER_HPP
#define CLIENT_CONNECTION_CONTROLLER_HPP

#include "Controllers/SocketController.hpp"
#include "Message.hpp"
#
class ClientConnectionController : public NetworkInformation {
public:
    ClientConnectionController(std::string ip = SERVER_IP, int port = SERVER_PORT) : NetworkInformation(port, ip) {
        try {
            server_sock = SocketController::createSocket();
        } catch (const std::runtime_error &e) {
            std::cerr << ERROR_SOCKET_CREATION << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }

        if (inet_pton(AF_INET, ip.c_str(), &address.sin_addr) <= 0) {
            std::cerr << ERROR_INVALID_IP << std::endl;
            exit(EXIT_FAILURE);
        }

        if (connect(server_sock, (struct sockaddr *)&address, sizeof(address)) < 0) {
            std::cerr << ERROR_CONNECTING << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << INFO_CONNECTED_TO_SERVER << ip << ":" << port << std::endl;
    }

    int getServerSocket() const { return server_sock; }

    ~ClientConnectionController() {
        SocketController::closeSocket(server_sock);
    }

    std::string getCommand() {
        return "";
    }

private:
    int server_sock = -1;
};

#endif // CLIENT_CONNECTION_CONTROLLER_HPP