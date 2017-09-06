#include <iostream>

class parent
{
public:
    // Constructor
    parent(int foo) : mFoo(foo)
    {
    }

    // Destructor
    ~parent();

    virtual void print() { std::cout << "parent mFoo: " << mFoo << std::endl; }

private:
    int mFoo;
};
