#include "singleton.h"

int main(void)
{
    for(int i = 0; i < 1024*1024; i++)
        singleton::instance()->print();

    return 0;
}

