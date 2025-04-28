#ifndef BEERSTOCK_HPP
#define BEERSTOCK_HPP

#include "Interface/IStock.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

class BeerStock : public IStock {
public:
    BeerStock() = default;

    BeerStock(const BeerStock&) = delete;
    BeerStock& operator=(const BeerStock&) = delete;

    double getPrice() const override { return price; }
    int getVolume() const override { return volume; }
    std::string getName() const override { return symbolName; }
    StockType getType() const override { return symbol; }
    std::string getCompanyName() const override { return companyName; }

    void setPrice(double newPrice) override {
        std::lock_guard<std::mutex> lock(stockMutex);
        price = newPrice;
    }

    void setVolume(int newVolume) override {
        std::lock_guard<std::mutex> lock(stockMutex);
        volume = newVolume;
    }

    void buyStock(int amount) override {
        std::lock_guard<std::mutex> lock(stockMutex);
        if (amount > volume) {
            throw std::invalid_argument("Not enough stock volume to buy.");
        }
        volume -= amount;
        //price += price * (static_cast<double>(amount) / (volume + amount)); // Increase price by the percentage of stock bought
    }

    void sellStock(int amount) override {
        std::lock_guard<std::mutex> lock(stockMutex);
        volume += amount;
        //price -= price * (static_cast<double>(amount) / (volume - amount)); // Decrease price by the percentage of stock sold
    }

    void updatePrice() override {
        std::lock_guard<std::mutex> lock(stockMutex);
        double newPrice = 0;
        int maxIncrease = 150; // in the positive part
        int maxDecrease = 100;  // in the negative part
        double divider = 10.0;
        int variableRate = maxIncrease + maxDecrease;

        while (newPrice <= startingPrice) {
            newPrice = price + ((rand() % variableRate) - maxDecrease) / divider; // Random price change between -10.0 and +15.0
        }
        price = newPrice;
    }

    std::string displayStockInfo() const override {
        std::ostringstream info;

        info << "Stock: " << symbolName << "\n"
            << "Company: " << companyName << "\n"
            << "Price: $" << price << "\n"
            << "Volume: " << volume;
        return info.str();
    }

private:
    double startingPrice = 1.0;
    double price = startingPrice;
    int volume = 1000;
    StockType symbol = StockType::BEER;
    std::string symbolName = "BEER";
    std::string companyName = "Generic Beer Company";
};

#endif // BEERSTOCK_HPP