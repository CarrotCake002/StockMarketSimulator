#ifndef STOCK_MANAGER_HPP
#define STOCK_MANAGER_HPP

#include "Interface/IStock.hpp"
#include "Controller/MessageController.hpp"
#include "Constants.hpp"

#include "BeerStock.hpp"

#include <vector>

class StockManager {
public:
    StockManager();
    ~StockManager();

    // Parse stock type from string
    StockType parseStockType(const std::string &type) const;

    // Update stock price
    void updatePrice(int client_socket);
    void displayStockInfo(int client_socket) const;
    void buyStock(const StockType symbol, int amount);
    void sellStock(const StockType symbol, int amount);

private:
    std::vector<IStock *> stocks; // Vector to hold pointers to stock objects
};

#endif // STOCK_MANAGER_HPP