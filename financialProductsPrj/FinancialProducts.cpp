#include "FinancialProducts.h"
#include <string>

// We can provide definition even to pure virtual functions 
// for general functionalities
std::string FinancialProduct::getDescription() const 
{
    return "This is a financial phenomenon"; 
}

std::string Asset::getDescription() const {
    return FinancialProduct::getDescription(); 
}
double Asset::getValue() const { return -1; }


Stock::Stock(const std::string& n, double price, int quantity)
    : Asset(n), pricePerShare(price), shares(quantity) {}

double Stock::getValue() const { return pricePerShare * shares; }

std::string Stock::getDescription() const {
    return "Stock: " + name + " | Price per Share: $" + std::to_string(pricePerShare) + " | Shares: " + std::to_string(shares);
}

Bond::Bond(const std::string& n, double faceValue, double rate)
    : Asset(n), faceValue(faceValue), interestRate(rate) {}

double Bond::getValue() const { return faceValue * (1 + interestRate); }

std::string Bond::getDescription() const {
    return "Bond: " + name + " | Face Value: $" + std::to_string(faceValue) + " | Interest Rate: " + std::to_string(interestRate * 100) + "%";
}

Portfolio::Portfolio(const std::string& n, double stockPrice, int stockQuantity, double bondFaceValue, double bondRate)
    : Asset(n), Stock(n, stockPrice, stockQuantity), Bond(n, bondFaceValue, bondRate) {}

double Portfolio::getValue() const { return Stock::getValue() + Bond::getValue(); }

std::string Portfolio::getDescription() const {
    return "Portfolio: " + name + "\n - " + Stock::getDescription() + "\n - " + Bond::getDescription();
}
