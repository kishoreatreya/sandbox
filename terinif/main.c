#include <stdio.h>

#define TRUE 1
#define FALSE 0

int
main()
{
    int a = 1;
    int b = 0;
    int c = 1;

    if(((a == b) ? TRUE : FALSE) && c)
    {
        printf("YAY!!\n");
    }
    else
    {
        printf("BOOO!!!\n");
    }
    return 0;
}

