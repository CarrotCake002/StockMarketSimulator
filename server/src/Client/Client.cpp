#include "Client/Client.hpp"

void Client::addFunds(double amount) {
    balance += amount;
}

void Client::buyStock(StockType type, int quantity) {
    double stockPrice = stockManager->getStockPrice(type);

    try {
        stockManager->buyStock(type, quantity);
    } catch (const std::invalid_argument& e) {
        throw e;
    }
    ownedStocks[type] += quantity;
    balance -= stockPrice * quantity;
}

void Client::sellStock(StockType type, int quantity) {
    double stockPrice = stockManager->getStockPrice(type);

    try {
        stockManager->sellStock(type, quantity);
    } catch (const std::invalid_argument& e) {
        throw e;
    }
    ownedStocks[type] -= quantity;
    balance += stockPrice * quantity;
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