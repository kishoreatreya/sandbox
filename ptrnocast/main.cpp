#include "child.h"

int main(void)
{
    parent* p = NULL;
    child*  c = NULL;
    parent* f = new child(10);

    f->print();

    c = dynamic_cast<child*>(f);

    c->print();

    p = c;
    p->print();

    return 0;
}
