#include <stdio.h>
#include <math.h>
#include <stdint.h>

int main(void)
{
    double x = 4;
    uint32_t szbyte = 8;

    printf("ceil check %f\n", ceil((x - 1) / szbyte) + 1);

    return 0;
}



