#include "FinancialProducts.h"
#include <string>

// Definition for pure virtual function in FinancialProduct
// for general functionality
std::string FinancialProduct::getDescription() const 
{
    return "This is a financial phenomenon";
}

// Call the base class's pure virtual function definition
std::string Asset::getDescription() const 
{
    return FinancialProduct::getDescription();
}

double Asset::getValue() const 
{
    return -1;  // Initial empty value
}

Stock::Stock(const std::string& n, double price, int quantity)
    : Asset(n), pricePerShare(price), shares(quantity) {}

// Return the total value of stock
double Stock::getValue() const 
{
    return pricePerShare * shares;  
}

std::string Stock::getDescription() const 
{
    return "Stock: " + name + " | Price per Share: $" + std::to_string(pricePerShare) +
        " | Shares: " + std::to_string(shares);
}

Bond::Bond(const std::string& n, double faceValue, double rate)
    : Asset(n), faceValue(faceValue), interestRate(rate) {}

// Return bond value including interest
double Bond::getValue() const 
{
    return faceValue * (1 + interestRate); 
}

std::string Bond::getDescription() const 
{
    return "Bond: " + name + " | Face Value: $" + std::to_string(faceValue) +
        " | Interest Rate: " + std::to_string(interestRate * 100) + "%";
}

Portfolio::Portfolio(const std::string& n, double stockPrice, int stockQuantity,
    double bondFaceValue, double bondRate)
    : Asset(n), Stock(n, stockPrice, stockQuantity), Bond(n, bondFaceValue, bondRate) {}

// Return combined value of portfolio
double Portfolio::getValue() const 
{
    return Stock::getValue() + Bond::getValue();  
}

std::string Portfolio::getDescription() const 
{
    return "Portfolio: " + name + "\n - " + Stock::getDescription() + "\n - " + Bond::getDescription();
}
