#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include "Controller/CommandController.hpp"
#include "Controller/ServerConnectionController.hpp"
#include "Client/Client.hpp"


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
    
        void handleClient(Client *client);
        void handleConnectedClient(Client *client);
        
        Client *getClient(int clientSocket);
        Client *createClient(int client_socket);
        void removeClient(Client *client);
    
    private:
        int port;
        ServerConnectionController server;
        StockManager* stockManager;
    
        std::vector<Client *> clients;
        std::mutex clientSocketsMutex;
    };
    

#endif // SERVER_MANAGER_HPP