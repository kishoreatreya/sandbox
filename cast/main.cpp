#include "child.h"


int main()
{
    base* b = new base(10);
    child* c = static_cast<child*>(b);

    b->getA();
    c->getA();

    return 0;
}
