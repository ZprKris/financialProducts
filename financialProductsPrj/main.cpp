#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "FinancialProducts.h"
#include "SharedPtr.h"

void displayFinancialProduct(const std::unique_ptr<FinancialProduct>& product) 
{
    std::cout << product->getDescription()
        << " | Total Value: $"
        << std::fixed << std::setprecision(2)
        << product->getValue()
        << std::endl << std::endl;
}

int main() 
{
    // Vector to store inventory of financial products
    std::vector<std::unique_ptr<FinancialProduct>> inventory;

    // Adding products to inventory using unique_ptr
    inventory.push_back(std::make_unique<Stock>("Tech Company", 150.00, 20));
    inventory.push_back(std::make_unique<Bond>("Government Bond", 1000.00, 0.05));
    inventory.push_back(std::make_unique<Portfolio>("Balanced Portfolio", 150.00, 10, 5000.00, 0.03));

    std::cout << "Financial Product Inventory:\n\n";

    // Displaying details of each financial product in the inventory
    for (const auto& product : inventory) 
    {
        // Each product is treated generically as a FinancialProduct, but thanks to polymorphism, 
        // each type (Stock, Bond, Portfolio) displays unique behavior in getValue() and getDescription() virtual functions 
        displayFinancialProduct(product);
    }

    // Using user-defined SharedPtr class to manage a Stock instance 
    SharedPtr<FinancialProduct> ptr1(new Stock("Tech Company", 150.00, 20));
    // Copying the shared pointer, because shared pointers should be aware of each other 
    // Count attribute should be incremented
    SharedPtr<FinancialProduct> ptr2 = ptr1;  

    return 0;
}

