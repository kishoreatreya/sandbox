#include <stdio.h>


#define OFFSET 65536

#define OFFSET_BY(x) ((x >= OFFSET) ? x - OFFSET : x)

int main (void)
{
    unsigned x = 128*1024;

    unsigned y = OFFSET_BY(x);

    printf("x: %d, y: %d\n", x, y);

    return 0;
}


