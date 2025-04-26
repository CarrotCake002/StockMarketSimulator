#include "ServerManager.hpp"

ServerManager::ServerManager(int port)
    : port(port), server(port), stockManager(new StockManager())
{}

ServerManager::~ServerManager() {
    delete stockManager;
}

void ServerManager::run() {
    server.listenForConnections();
    startStockUpdater();
    acceptClientsLoop();
    SocketController::closeSocket(server.getServerSocket());
}

void ServerManager::startStockUpdater() {
    std::thread([this]() {
        while (!serverShutdown) {
            std::this_thread::sleep_for(std::chrono::seconds(10));

            std::lock_guard<std::mutex> lock(clientSocketsMutex);
            for (int socket : clientSockets) {
                stockManager->updatePrice(socket);
            }
        }
    }).detach();
}

void ServerManager::acceptClientsLoop() {
    while (!serverShutdown) {
        int clientSocket = server.acceptConnection();

        if (clientSocket < 0)
            continue;

        {
            std::lock_guard<std::mutex> lock(clientSocketsMutex);
            clientSockets.push_back(clientSocket);
        }

        std::thread(&ServerManager::handleClient, this, clientSocket).detach();

        std::cout << "[INFO] Client connected: FD " << clientSocket << std::endl;
    }
}

void ServerManager::handleClient(int clientSocket) {
    handleConnectedClient(clientSocket);

    removeClient(clientSocket);
    SocketController::closeSocket(clientSocket);

    std::cout << "[INFO] Client disconnected: FD " << clientSocket << std::endl;
}

void ServerManager::removeClient(int clientSocket) {
    std::lock_guard<std::mutex> lock(clientSocketsMutex);
    clientSockets.erase(
        std::remove(clientSockets.begin(), clientSockets.end(), clientSocket),
        clientSockets.end()
    );
}

void ServerManager::handleConnectedClient(int client_socket) {
    CommandController commandController(client_socket, stockManager);

    while (!serverShutdown) {
        try {
            std::string clientInput = ServerMessage::receiveMessage(client_socket);
            Command command = commandController.parseCommand(clientInput);

            commandController.executeCommand(command, clientInput);
        } catch (const Exception::ClientDisconnected &e) {
            ServerMessage::sendMessage(client_socket, INFO_CLIENT_DISCONNECTED);
            break;
        } catch (const std::invalid_argument &e) {
            std::cerr << ERROR << e.what() << std::endl;
            ServerMessage::sendMessage(client_socket, e.what());
            continue;
        } catch (const std::runtime_error &e) {
            std::cerr << ERROR << e.what() << std::endl;
            ServerMessage::sendMessage(client_socket, ERROR_RUNTIME);
            continue;
        } catch (std::exception &e) {
            std::cerr << ERROR << e.what() << std::endl;
            ServerMessage::sendMessage(client_socket, ERROR_PROCESSING_COMMAND);
            continue;
        }
    }
    SocketController::closeSocket(client_socket);
}

