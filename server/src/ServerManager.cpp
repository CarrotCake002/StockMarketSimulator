#include "ServerManager.hpp"

ServerManager::ServerManager(int port)
    : port(port), server(port), stockManager(new StockManager())
{}

ServerManager::~ServerManager() {
    for (auto client : clients) {
        delete client;
    }
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
            
            for (auto client : clients) {
                stockManager->updatePrice(client->getSocket());
            }
        }
    }).detach();
}

Client *ServerManager::getClient(int clientSocket) {
    std::lock_guard<std::mutex> lock(clientSocketsMutex);
    
    auto it = std::find_if(clients.begin(), clients.end(), [clientSocket](Client* client) {
        return client->getSocket() == clientSocket;
    });
    
    if (it != clients.end()) {
        return *it;
    }
    return nullptr;
}

Client *ServerManager::createClient(int clientSocket) {
        std::lock_guard<std::mutex> lock(clientSocketsMutex);

        Client *client = new Client(clientSocket, stockManager);
        clients.push_back(client);
        return client;
}

void ServerManager::removeClient(Client *client) {
    std::lock_guard<std::mutex> lock(clientSocketsMutex);
    
    clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
    delete client;
}

void ServerManager::acceptClientsLoop() {
    while (!serverShutdown) {
        int clientSocket = server.acceptConnection();

        if (clientSocket < 0)
            continue;

        Client *newClient = createClient(clientSocket);
        std::thread(&ServerManager::handleClient, this, newClient).detach();

        std::cout << "[INFO] Client connected: FD " << clientSocket << std::endl;
    }
}

void ServerManager::handleClient(Client *client) {
    handleConnectedClient(client);
    int clientSocket = client->getSocket();

    SocketController::closeSocket(clientSocket);
    removeClient(client);

    std::cout << "[INFO] Client disconnected: FD " << clientSocket << std::endl;
}

void ServerManager::handleConnectedClient(Client *client) {
    int clientSocket = client->getSocket();
    CommandController commandController(clientSocket, stockManager);

    while (!serverShutdown) {
        try {
            std::string clientInput = ServerMessage::receiveMessage(clientSocket);
            Command command = commandController.parseCommand(clientInput);

            commandController.executeCommand(command, clientInput, client);
        } catch (const Exception::ClientDisconnected &e) {
            ServerMessage::sendMessage(clientSocket, INFO_CLIENT_DISCONNECTED);
            break;
        } catch (const std::invalid_argument &e) {
            std::cerr << ERROR << e.what() << std::endl;
            ServerMessage::sendMessage(clientSocket, e.what());
            continue;
        } catch (const std::runtime_error &e) {
            std::cerr << ERROR << e.what() << std::endl;
            ServerMessage::sendMessage(clientSocket, ERROR_RUNTIME);
            continue;
        } catch (std::exception &e) {
            std::cerr << ERROR << e.what() << std::endl;
            ServerMessage::sendMessage(clientSocket, ERROR_PROCESSING_COMMAND);
            continue;
        }
    }
    SocketController::closeSocket(clientSocket);
}

