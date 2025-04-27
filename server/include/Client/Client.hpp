#ifndef CLIENT_HPP
#define CLIENT_HPP

// Client.hpp
#pragma once

#include "Stocks/StockType.hpp"
#include "Stocks/StockManager.hpp"

#include <string>
#include <unordered_map>


class Client {
public:
    Client(int socket, StockManager *stockManager): socket(socket), stockManager(stockManager){};

    int getSocket() const { return socket; };
    bool isLoggedIn() const { return loggedIn; };

    void login(const std::string& username);

    void addFunds(double amount);
    void buyStock(StockType type, int quantity);
    void sellStock(StockType type, int quantity);

    double getBalance() const { return balance; };
    int getStockHoldings(StockType type) const;

    std::string getClientInfo() const;

private:
    int socket;
    bool loggedIn;
    std::string username;
    double balance = 100.0;

    StockManager *stockManager;
    std::unordered_map<StockType, int> ownedStocks;
};


#endif // CLIENT_HPP