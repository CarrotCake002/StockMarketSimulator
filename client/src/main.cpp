#include "ClientConnectionManager.hpp"

int main() {
    ClientConnectionManager client;
    std::string clientCommand;
    std::string serverResponse;

    while (true) {
        std::getline(std::cin, clientCommand);
        Message::sendMessage(client.getServerSocket(), clientCommand);
        serverResponse = Message::receiveMessage(client.getServerSocket());
        std::cout << "Response from server: " << serverResponse << std::endl;
    }
    return 0;
}
