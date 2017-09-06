#include <stdio.h>

int main(void)
{
    int x = 0;
    int i = 0;
    
    printf("x: %d\n", x);

    for(i = 0; i <= 1; i++)
    {
        x |= (1 << i);
        printf("x: %d\n", x);
    }

    return 0;
}
