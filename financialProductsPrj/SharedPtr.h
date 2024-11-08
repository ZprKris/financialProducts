/*
SMART POINTERS:

Raw pointer variables have no inherent mechanism to clean up after themselves, so
programmers need always to do the deallocation themselves.
This task becomes cumbersome when a function has more than one exit point.
In such case, the cleanup should be done for each exit point in order to prevent memory leaks.

To make this task easier, we can use smart pointers.
A smart pointer is a composition class that is designed to manage dynamically allocated memory and ensure
that memory gets deleted when the smart pointer object goes out of scope.

There are different types of smart pointers: std::unique_ptr and std::shared_ptr.
In this project, std::shared_ptr is implemented and std::unique_ptr is used directly.
*/

/*
SHARED AND UNIQUE POINTERS:

std::unique_ptr is designed to singly own and manage a resource, std::shared_ptr is
meant to solve the case where you need multiple smart pointers co-owning a resource.
Internally, std::shared_ptr keeps track of how many std::shared_ptr are sharing the resource.
As long as at least one std::shared_ptr is pointing to the resource,
the resource will not be deallocated, even if individual std::shared_ptr are destroyed.

std::shared_ptr instances must know about each other!
*/

/*
MOVE SEMANTICS:

We use move semantics to prevent copying the objects in unnecessary cases, when objects
are stored in temporary objects and will not be used later in the program.
Move copy constructor and assignment take in rvalue references (however, automatic objects returned
from a function by value can be moved even if they are l-values, because they are temporary).
*/

/*
TEMPLATE:

Both the declaration and implementation of the SharedPtr template class are provided in the same header file.
This is because compiler needs access to the template definition at the point of instantiation. 
This ensures that the compiler can generate both the declaration and definition versions of the 
template for a specific type. 
*/

#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <iostream>

template <typename T>
class SharedPtr 
{
private:
    // Raw pointer
    T* m_ptr;
    // Count of instances
    size_t* m_cnt;

public:
    // Constructor
    explicit SharedPtr(T* p = nullptr);
    // Copy Constructor
    SharedPtr(const SharedPtr<T>& other);
    // Move Constructor
    SharedPtr(SharedPtr<T>&& other) noexcept;
    ~SharedPtr();

    // Assignment Operator
    SharedPtr& operator=(const SharedPtr& other);
    // Move Assignment Operator
    SharedPtr& operator=(SharedPtr&& other) noexcept;

    T& operator*() const;
    T* operator->() const;
    T* get_ptr() const;
    size_t get_cnt() const;
};

// Constructor
template <typename T>
SharedPtr<T>::SharedPtr(T* p) : m_ptr(p), m_cnt(new size_t(1)) 
{
    std::cout << "Shared pointer created. Count: " << *m_cnt << std::endl;
}

// Copy constructor
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) : m_ptr(other.m_ptr), m_cnt(other.m_cnt) 
{
    ++(*m_cnt);
    std::cout << "Shared pointer copied. Count: " << *m_cnt << std::endl;
}

// Move constructor
template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept : m_ptr(other.m_ptr), m_cnt(other.m_cnt) 
{
    other.m_ptr = nullptr;
    other.m_cnt = nullptr;
    std::cout << "Shared pointer moved." << std::endl;
}

// Destructor
template <typename T>
SharedPtr<T>::~SharedPtr() 
{
    if (m_cnt && --(*m_cnt) == 0) {
        delete m_ptr;
        delete m_cnt;
        std::cout << "Shared pointer cleaned-up." << std::endl;
    }
}

// Copy assignment operator
template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) 
{
    if (this != &other) {
        if (m_cnt && --(*m_cnt) == 0) {
            delete m_ptr;
            delete m_cnt;
            std::cout << "Shared pointer cleaned-up." << std::endl;
        }
        m_ptr = other.m_ptr;
        m_cnt = other.m_cnt;
        ++(*m_cnt);
        std::cout << "Shared pointer assigned. Count: " << *m_cnt << std::endl;
    }
    return *this;
}

// Move assignment operator
template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept 
{
    if (this != &other) {
        if (m_cnt && --(*m_cnt) == 0) {
            delete m_ptr;
            delete m_cnt;
            std::cout << "Shared pointer cleaned-up." << std::endl;
        }
        m_ptr = other.m_ptr;
        m_cnt = other.m_cnt;
        other.m_ptr = nullptr;
        other.m_cnt = nullptr;
        std::cout << "Shared pointer moved and assigned." << std::endl;
    }
    return *this;
}

template <typename T>
T& SharedPtr<T>::operator*() const 
{
    return *m_ptr;
}

template <typename T>
T* SharedPtr<T>::operator->() const 
{
    return m_ptr;
}

template <typename T>
T* SharedPtr<T>::get_ptr() const 
{
    return m_ptr;
}

template <typename T>
size_t SharedPtr<T>::get_cnt() const 
{
    return m_cnt ? *m_cnt : 0;
}


#endif
