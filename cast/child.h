#ifndef _CHILD_H_
#define _CHILD_H_
#include "base.h"

class child : public base 
{
public:
    child(int a) : base(a)
    {
    }

    virtual int getA()
    {
        std::cout << "dump child ma: " << mA << std::endl;
        return mA;
    }

};

#endif // _CHILD_H_
