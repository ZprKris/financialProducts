/*
KEYWORD VIRTUAL - Polymorphism

Polymorphism simplifies our code by using a common interface for different types.
One way to achieve polymorphism is through runtime polymorphism, which uses virtual functions.

We can use pointers or references to a base class to simplify the code. When we use a pointer or 
reference to a base class, it can call the derived class version of a function instead of the base class version, 
but only if the function is declared as virtual in the base class.

Virtual function resolution works when a virtual function is called through a pointer or reference to a base 
class object. This mechanism works because the compiler can differentiate between the type of the pointer/reference 
(which is the base class) and the actual type of the object it points to (a derived class). 
This allows the correct, derived class version of the function to be called at runtime.
*/

/*
KEYWORD VIRTUAL - Abstract classes

We can use pure virtual functions to create an abstract base class, which cannot be instantiated directly. 
A pure virtual function is a virtual function that is declared with = 0. This indicates that it has no 
implementation in the base class and must be overridden by derived classes.

However, we can still define pure virtual functions in the base class to provide general functionalites for the derived classes. 

An interface class is a special type of abstract class that has no member variables and where all functions are pure virtual. 
*/


#ifndef FINANCIALPRODUCT_H
#define FINANCIALPRODUCT_H

#include <string>

// Interface class 
class FinancialProduct 
{
public:
    // If we plan a class to be used as a base class, its destructor should be virtual to ensure proper cleanup in derived classes.
    virtual ~FinancialProduct() = default;
    virtual double getValue() const = 0;
    virtual std::string getDescription() const = 0;
};

// Base class for Stock and Bond classes to create a diamond inheritance.
class Asset : public FinancialProduct 
{
protected:
    std::string name;

public:
    // The explicit keyword prevents this constructor from being used as a conversion constructor.
    explicit Asset(const std::string& n) : name(n) {}
    std::string getDescription() const override;
    double getValue() const override;

};

// Stock class inherits from Asset class.
// Virtual inheritance ensures a single instance of the Asset class in derived classes.
class Stock : public virtual Asset 
{
private:
    double pricePerShare;
    int shares;

public:
    Stock(const std::string& n, double price, int quantity);
    double getValue() const override;
    std::string getDescription() const override;
};

// Bond class inherits from Asset class.
// Virtual inheritance ensures a single instance of the Asset class in derived classes.
class Bond : public virtual Asset 
{
private:
    double faceValue;
    double interestRate;

public:
    Bond(const std::string& n, double faceValue, double rate);
    double getValue() const override;
    std::string getDescription() const override;
};

// Portfolio class inherits from both Stock and Bond, creating diamond inheritance.
class Portfolio : public Stock, public Bond 
{
public:
    Portfolio(const std::string& n, double stockPrice, int stockQuantity, double bondFaceValue, double bondRate);
    double getValue() const override;
    std::string getDescription() const override;
};

#endif
