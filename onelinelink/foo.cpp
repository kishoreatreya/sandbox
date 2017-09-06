#include "foo.h"

using namespace std;

foo::foo(int a) : mFoo(a)
{
}

void foo::dump()
{
    cout << "mFoo: " << mFoo << endl;
}


