#ifndef STOCKMANAGER_HPP
#define STOCKMANAGER_HPP

#include "StockManager.hpp"

StockManager::StockManager() {
    IStock* beerStock = new BeerStock();

    stocks.push_back(beerStock);
}

StockManager::~StockManager() {
    for (auto& stock : stocks) {
        delete stock;
    }
}

void StockManager::updatePrice(void) {
    for (auto& stock : stocks) {
        stock->updatePrice();
    }
}

void StockManager::buyStock(const StockType symbol, int amount) {
    for (auto& stock : stocks) {
        if (stock->getType() == symbol) {
            stock->buyStock(amount);
            return;
        }
    }
    throw std::invalid_argument("Stock not found.");
}

#endif // STOCKMANAGER_HPP