#ifndef SERVER_RESPONSE_CONTROLLER_HPP
#define SERVER_RESPONSE_CONTROLLER_HPP

#include "Atomic.hpp"
#include "Constants.hpp"
#include "Message.hpp"

#include <iostream>
#include <string>
#include <thread>

class ServerResponseController {
public:
    ServerResponseController(int serverSocket) : serverSocket(serverSocket) {
        createServerResponseThread();
    };

    static void handleServerResponse(int serverSocket) {
        std::string serverResponse;

        while (!serverShutdown && !clientExit) {
            try {
                serverResponse = Message::receiveMessage(serverSocket);
                std::cout << RESPONSE << serverResponse << std::endl;
            } catch (const Exception::ClientDisconnected &e) {
                clientExit = true;
                std::cerr << ERROR << e.what() << std::endl;
                break;
            } catch (...) {
                std::cerr << ERROR << ERROR_UNEXPECTED << std::endl;
                break;
            }
        }
    }

    void createServerResponseThread(void) const {
        std::thread serverResponseThread(handleServerResponse, serverSocket);
        serverResponseThread.detach();
    }

private:
    int serverSocket;
};

#endif // SERVER_RESPONSE_CONTROLLER_HPP