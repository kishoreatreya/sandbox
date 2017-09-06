#include <stdio.h>

#define N 5

int arr[N] = { 0, 0, 10, 0, 10};

int main(void)
{
    int i = 0, j = N-1;
    int iter = 0;

    while(i < j-1)
    {
        printf("iter: %d\n", iter);
        if(arr[i] != 0)
        {
            printf("i != 0, %d\n", i);
            i++;
        }

        if(arr[j] == 0)
        {
            printf("j == 0, %d\n", j);
            j--;
        }

        if((arr[i] == 0) && (arr[j] != 0))
        {
            printf("preswap: arr[i]; %d, arr[j] = %d, i = %d, j = %d\n", arr[i], arr[j], i, j);
            arr[i] = arr[i] ^ arr[j];
            arr[j] = arr[i] ^ arr[j];
            arr[i] = arr[i] ^ arr[j];
            printf("postswap: arr[i]; %d, arr[j] = %d, i = %d, j = %d\n", arr[i], arr[j], i, j);
        }
        iter++;
    }

    for(i = 0; i < N; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    return 0;
}


