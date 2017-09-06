#include <stdio.h>
#include <string.h>

int main()
{
    int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int b[10] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    int i = 0;

    memcpy(a, b, 4);

    for(i = 0; i < 10; i++)
    {
        printf("a[%d] = %d\n", i, a[i]);
    }

    return 0;
}
