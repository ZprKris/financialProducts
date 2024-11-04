/*
KEYWORD VIRTUAL - Polymorphism

We can simplify code by using polymorphism.
Runtime polymorphism: virtual functions.

We can simplify code by using pointers or references to a base class.
Base pointers will call the derived version of a function instead of the base version, only when
we use virtual functions in base class.

Virtual function resolution only works when a virtual member function is called through a pointer or
reference to a class type object. This works because the compiler can differentiate the type of the pointer
or reference from the type of the object being pointed to or referenced.

*/

/*
KEYWORD VIRTUAL - Abstract classes

We can use pure virtual functions to create abstract base class, which can not be instantiated.
We can create pure virtual functions that have definitions. It is useful when we wan base class
to provide a default implementation for a function, but still force any derived classes to provide
their own implementation.

An interface class is a class that has no member variables, and where all of the functions are pure virtual!
*/


#ifndef FINANCIALPRODUCT_H
#define FINANCIALPRODUCT_H

#include <string>
// Interface class 
class FinancialProduct {
public:
    // Whenever we are dealing with inheritance, we should make any explicit destructors virtual, 
    // when we plan a class to be a base class. 
    virtual ~FinancialProduct() = default;
    virtual double getValue() const = 0;
    virtual std::string getDescription() const = 0;
};

// Base class for Stock and Bond for a diamond inheritance
class Asset : public FinancialProduct {
protected:
    std::string name;

public:
    // We use the explicit keyword to tell the compiler that a constructor should 
    // not be used as a converting constructor.
    explicit Asset(const std::string& n) : name(n) {}
    std::string getDescription() const override;
    double getValue() const override;

};

// Stock class inherits from Asset
// We use virtual keyword to esnure that there's a single instance of the Asset class
class Stock : public virtual Asset {
private:
    double pricePerShare;
    int shares;

public:
    Stock(const std::string& n, double price, int quantity);
    double getValue() const override;
    std::string getDescription() const override;
};

// Bond class inherits from Asset
// We use virtual keyword to esnure that there's a single instance of the Asset class
class Bond : public virtual Asset {
private:
    double faceValue;
    double interestRate;

public:
    Bond(const std::string& n, double faceValue, double rate);
    double getValue() const override;
    std::string getDescription() const override;
};

// Portfolio class inherits from both Stock and Bond
class Portfolio : public Stock, public Bond {
public:
    Portfolio(const std::string& n, double stockPrice, int stockQuantity, double bondFaceValue, double bondRate);
    double getValue() const override;
    std::string getDescription() const override;
};

#endif
