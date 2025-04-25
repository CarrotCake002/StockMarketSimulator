#ifndef STOCK_MANAGER_HPP
#define STOCK_MANAGER_HPP

#include "IStock.hpp"

#include "BeerStock.hpp"

#include <vector>

class StockManager {
public:
    StockManager() = default;
    ~StockManager();

    // Update stock price
    void updatePrice(void);

    void buyStock(const StockType symbol, int amount);

private:
    std::vector<IStock *> stocks; // Vector to hold pointers to stock objects
};

#endif // STOCK_MANAGER_HPP