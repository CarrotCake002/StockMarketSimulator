#ifndef ISTOCK_HPP
#define ISTOCK_HPP

#include <string>

enum class StockType {
    BEER,
    WINE
};

class IStock {
public:
    virtual ~IStock() = default;
    
    virtual double getPrice(void) const = 0;
    virtual void setPrice(double price) = 0;
    
    virtual int getVolume(void) const = 0;
    virtual void setVolume(int volume) = 0;
    
    virtual std::string getSymbolName(void) const = 0;
    virtual StockType getType(void) const = 0;

    virtual std::string getCompanyName(void) const = 0;

    virtual void updatePrice(void) = 0;
    virtual void buyStock(int amount) = 0;
};

#endif // ISTOCK_HPP