#ifndef ISTOCK_HPP
#define ISTOCK_HPP

#include <string>
#include <mutex>
#include <sstream>

#include "Stocks/StockType.hpp"

class IStock {
public:
    virtual ~IStock() = default;
    
    virtual double getPrice(void) const = 0;
    virtual void setPrice(double price) = 0;
    
    virtual int getVolume(void) const = 0;
    virtual void setVolume(int volume) = 0;

    virtual std::string getName(void) const = 0;
    virtual StockType getType(void) const = 0;

    virtual std::string getCompanyName(void) const = 0;

    virtual void updatePrice(void) = 0;
    virtual void buyStock(int amount) = 0;
    virtual void sellStock(int amount) = 0;

    virtual std::string displayStockInfo(void) const = 0;

protected:
    std::mutex stockMutex;
};

#endif // ISTOCK_HPP