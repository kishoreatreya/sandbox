#ifndef _BASE_H_
#define _BASE_H_

#include <iostream>

class base
{
public:
    base(int a) : mA(a)
    {
    }

    virtual int getA()
    {
        std::cout << "dump base ma: " << mA << std::endl;
        return mA;
    }

protected:
    int mA;

};

#endif // _CHILD_H_
