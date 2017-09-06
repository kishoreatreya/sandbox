#include <stdio.h>

int main()
{   
    char barr[4];
    unsigned int  val = 0xFFF;

    barr[0] = val & 0xFF;
    barr[1] = val >> 8;
    barr[2] = barr[3] = 0;

    printf("barr = 0x%hhx%hhx%hhx%hhx\n", barr[3], barr[2], barr[1], barr[0]);


    return 0;
}
