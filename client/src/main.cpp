#include "ClientConnectionManager.hpp"

int main() {
    ClientConnectionManager connectionManager;

    std::string message = Message::receiveMessage(connectionManager.getClientSocket());
    std::cout << "Message from server: " << message << std::endl;
    Message::sendMessage(connectionManager.getClientSocket(), "Hello from client!");
    return 0;
}
