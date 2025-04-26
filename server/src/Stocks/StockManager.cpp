#include "Stocks/StockManager.hpp"

StockManager::StockManager() {
    IStock* beerStock = new BeerStock();

    stocks.push_back(beerStock);
}

StockManager::~StockManager() {
    for (auto& stock : stocks) {
        delete stock;
    }
}

StockType StockManager::parseStockType(const std::string &type) const {
    if (type == "BEER") {
        return StockType::BEER;
    } else if (type == "WINE") {
        return StockType::WINE;
    } else {
        throw std::invalid_argument(ERROR_STOCK_NOT_FOUND);
    }
}

void StockManager::updatePrice(int client_socket) {
    std::ostringstream info;

    for (auto& stock : stocks) {
        stock->updatePrice();
        info << stock->displayStockInfo() << "\n";
    }
    Message::sendMessage(client_socket, info.str());
}

void StockManager::displayStockInfo(int client_socket) const {
    std::ostringstream info;
    for (const auto& stock : stocks) {
        info << "\n" << stock->displayStockInfo();
    }
    Message::sendMessage(client_socket, info.str());
}

void StockManager::buyStock(const StockType symbol, int amount) {
    for (auto& stock : stocks) {
        if (stock->getType() == symbol) {
            stock->buyStock(amount);
            return;
        }
    }
    throw std::invalid_argument(ERROR_STOCK_NOT_FOUND);
}

void StockManager::sellStock(const StockType symbol, int amount) {
    for (auto& stock : stocks) {
        if (stock->getType() == symbol) {
            stock->sellStock(amount);
            return;
        }
    }
    throw std::invalid_argument(ERROR_STOCK_NOT_FOUND);
}
