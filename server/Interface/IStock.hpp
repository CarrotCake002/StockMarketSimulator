#ifndef ISTOCK_HPP
#define ISTOCK_HPP

#include <string>

class IStock {
public:
    virtual ~IStock() = default;
    
    virtual double getPrice() const = 0;
    virtual void setPrice(double price) = 0;
    
    virtual int getVolume() const = 0;
    virtual void setVolume(int volume) = 0;
    
    // Get the stock symbol (e.g., "AAPL", "GOOGL")
    virtual std::string getSymbol() const = 0;

    virtual std::string getCompanyName() const = 0;

    virtual void updatePrice(void) = 0;
};

#endif // ISTOCK_HPP