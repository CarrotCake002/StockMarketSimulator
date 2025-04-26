#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include "Controller/CommandController.hpp"
#include "Controller/ServerConnectionController.hpp"

#include <thread>
#include <chrono>
#include <algorithm>
#include <iostream>

class ServerManager {
    public:
        ServerManager(int port);
        ~ServerManager();
    
        void run(); // Start the server
    private:
        void startStockUpdater();
        void acceptClientsLoop();
        void handleClient(int client_socket);
        void handleConnectedClient(int client_socket);
        void removeClient(int client_socket);
    
    private:
        int port;
        ServerConnectionController server;
        StockManager* stockManager;
        std::vector<int> clientSockets;
        std::mutex clientSocketsMutex;
    };
    

#endif // SERVER_MANAGER_HPP