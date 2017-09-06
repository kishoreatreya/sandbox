#include <iostream>

#include "overload.h"
int main()
{
    foo* o = new foo();
    uint8_t bar = 10;

    o->print(bar);

    return 1;
}
