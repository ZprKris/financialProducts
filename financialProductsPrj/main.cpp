#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "FinancialProducts.h"
#include "SharedPtr.h"

void displayFinancialProduct(const std::unique_ptr<FinancialProduct>& product) {
    std::cout << product->getDescription() << " | Total Value: $" << std::fixed << std::setprecision(2) << product->getValue() << std::endl << std::endl;
}

int main() {
    std::vector<std::unique_ptr<FinancialProduct>> inventory;

    inventory.push_back(std::make_unique<Stock>("Tech Company", 150.00, 20));
    inventory.push_back(std::make_unique<Bond>("Government Bond", 1000.00, 0.05));
    inventory.push_back(std::make_unique<Portfolio>("Balanced Portfolio", 150.00, 10, 5000.00, 0.03));

    std::cout << "Financial Product Inventory:\n\n";
    for (const auto& product : inventory) {
        displayFinancialProduct(product);
    }

    SharedPtr<FinancialProduct> ptr1(new Stock("Tech Company", 150.00, 20));
    SharedPtr<FinancialProduct> ptr2 = ptr1;


    return 0;
}
