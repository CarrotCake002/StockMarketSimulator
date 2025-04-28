#include "Client/Client.hpp"

void Client::addFunds(double amount) {
    balance += amount;
}

bool Client::buyStock(StockType type, int quantity) {
    double stockPrice = stockManager->getStockPrice(type);
    double newBalance = 0;

    newBalance = balance - stockPrice * quantity;
    if (newBalance < 0)
        return false;
    balance = newBalance;
    ownedStocks[type] += quantity;
    try {
        stockManager->buyStock(type, quantity);
    } catch (const std::invalid_argument& e) {
        throw e;
    }
    return true;
}

bool Client::sellStock(StockType type, int quantity) {
    double stockPrice = stockManager->getStockPrice(type);
    int newOwnedStock = ownedStocks[type] - quantity;
    
    if (newOwnedStock < 0)
        return false;
    ownedStocks[type] = newOwnedStock;
    balance += stockPrice * quantity;
    try {
        stockManager->sellStock(type, quantity);
    } catch (const std::invalid_argument& e) {
        throw e;
    }
    return true;
}

int Client::getStockHoldings(StockType type) const {
    auto it = ownedStocks.find(type);

    if (it != ownedStocks.end()) {
        return it->second;
    }
    return 0;
}

std::string Client::getClientInfo() const {
    std::ostringstream info;

    info << "Client: " << username << "\n"
         << "Balance: " << balance << "\n"
         << "Stocks: \n";

    for (const auto& stock : ownedStocks) {
        info << "  - " << stockManager->getStockName(stock.first) << ": " << stock.second << "\n";
    }
    return info.str();
}