#include "ClientConnectionManager.hpp"

int main() {
    ClientConnectionManager client;

    std::string message = Message::receiveMessage(client.getClientSocket());
    std::cout << "Message from server: " << message << std::endl;
    Message::sendMessage(client.getClientSocket(), "Hello from client!");
    return 0;
}
