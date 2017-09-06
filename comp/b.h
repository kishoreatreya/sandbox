#include <iostream>

class B
{
private: 
    int mFoo;

public:
    B(int foo): mFoo(foo)
    {
        std::cout << "B is constructed with foo: " << mFoo << std::endl;
    }

    ~B()
    {
        std::cout << "B is deleted" << std::endl;
    }
};
