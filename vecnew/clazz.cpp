#include "clazz.h"
#include <iostream>

clazz::clazz(int k)
{
    std::cout << "Constructed clazz" << std::endl;
    this->k = k;
}

void
clazz::dump(int i)
{
    std::cout << "clazz printing i = " << i << " member k = " << k << std::endl;
}

