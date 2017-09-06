#include "singleton.h"

singleton* singleton::mInstance = NULL;

singleton*
singleton::instance()
{
    if(!mInstance)
        mInstance = new singleton();
    return mInstance;
}

