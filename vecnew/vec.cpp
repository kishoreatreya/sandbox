#include <cstdio>
#include <iostream>
#include "clazz.h"
#include <vector>

int
main()
{

    std::vector<clazz *> v;
    std::vector<clazz> k;

    v.resize(10, new clazz(40));

    for(int i = 0; i < 10; i++)
    {
        if(i == 5)
            v[i]->k = 20;
        v[i]->dump(i);
    }

    k.resize(10, clazz(80));
    
    for(int i = 0; i < 10; i++)
    {
        if(i == 5)
            k[i].k = 20;
 
        k[i].dump(i);
    }


    return 0;
}
