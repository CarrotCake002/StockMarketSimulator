#ifndef SERVER_RESPONSE_CONTROLLER_HPP
#define SERVER_RESPONSE_CONTROLLER_HPP

#include "Atomic.hpp"
#include "Constants.hpp"
#include "Controller/ClientMessageController.hpp"

#include <iostream>
#include <string>
#include <thread>

class ServerResponseController {
public:
    ServerResponseController(int serverSocket) : serverSocket(serverSocket) {
        createServerResponseThread();
    };

    static void displayServerResponse(const std::string& message) {
        std::cout   << "\33[2K\r"        // Clear line and return carriage
                    << message << "\n"   // Print server message on clean line
                    << "> " << std::flush; // Reprint the input prompt
    }

    static void handleServerResponse(int serverSocket) {
        std::string serverResponse;

        while (!serverShutdown && !clientExit) {
            try {
                serverResponse = ClientMessage::receiveMessage(serverSocket);
                displayServerResponse(serverResponse);
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