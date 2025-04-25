#ifndef BEERSTOCK_HPP
#define BEERSTOCK_HPP

#include "IStock.hpp"

#include <stdexcept>

class BeerStock : public IStock {
public:
    BeerStock() = default;

    BeerStock(const BeerStock&) = delete;
    BeerStock& operator=(const BeerStock&) = delete;

    double getPrice() const override { return price; }
    int getVolume() const override { return volume; }
    std::string getSymbolName() const override { return symbolName; }
    StockType getType() const override { return symbol; }
    std::string getCompanyName() const override { return companyName; }

    void setPrice(double newPrice) override {
        price = newPrice;
    }

    void setVolume(int newVolume) override {
        volume = newVolume;
    }

    void buyStock(int amount) override {
        if (amount > volume) {
            throw std::invalid_argument("Not enough stock volume to buy.");
        }

        volume -= amount;
        price += price * (static_cast<double>(amount) / (volume + amount)); // Increase price by the percentage of stock bought
    }

    void updatePrice() override {
        price += ((rand() % 200) - 100) / 10.0; // Random price change between -10.0 and +10.0
    }

private:
    double price = 100.0;
    int volume = 0;
    StockType symbol = StockType::BEER;
    std::string symbolName = "BEER";
    std::string companyName = "Generic Beer Company";
};

#endif // BEERSTOCK_HPP