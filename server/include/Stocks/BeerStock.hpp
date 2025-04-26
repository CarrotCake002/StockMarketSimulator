#ifndef BEERSTOCK_HPP
#define BEERSTOCK_HPP

#include "Interface/IStock.hpp"

#include <iostream>
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
        price += price * (static_cast<double>(amount) / (volume + amount)); // Increase price by the percentage of stock bought
    }

    void sellStock(int amount) override {
        std::lock_guard<std::mutex> lock(stockMutex);
        int originalVolume = volume; // Store the original volume
        volume += amount;
        price -= price * (static_cast<double>(amount) / originalVolume); // Decrease price by the percentage of stock sold
    }

    void updatePrice() override {
        std::lock_guard<std::mutex> lock(stockMutex);
        price += ((rand() % 200) - 100) / 10.0; // Random price change between -10.0 and +10.0
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
    double price = 100.0;
    int volume = 1000;
    StockType symbol = StockType::BEER;
    std::string symbolName = "BEER";
    std::string companyName = "Generic Beer Company";
};

#endif // BEERSTOCK_HPP