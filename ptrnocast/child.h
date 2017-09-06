#include <iostream>
#include "parent.h"

class child : public parent
{
public:
    // Constructor
    child(int foo) : parent(2 * foo),
                     mFoo(foo)
    {
    }

    // Destructor
    ~child();

    virtual void print() { std::cout << "child: mFoo: " << mFoo << std::endl; }

private:
    int mFoo;
};
