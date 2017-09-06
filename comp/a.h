#include <iostream>
#include "b.h"


class A
{
private: 
    B foo;

public:
    A(): foo(10)
    {
        std::cout << "A is constructed" << std::endl;
    }

    ~A()
    {
        std::cout << "A is deleted" << std::endl;
    }
};
