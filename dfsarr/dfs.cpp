#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "XpBitVector.h"

int* arr;

int dfs(int s, int cur)
{
    int i;
    int ret;

    if(cur > 1000000)
        return -1;

    if(arr[cur] == s)
        return cur;

    for(i = 1; i <= 2; i++)
    {
        ret = dfs(s, 2 * cur + i);
        if(ret != -1)
            return cur;
    }

    return -1;
}

void allocateBv(int size)
{

}

int main()
{
    int f = -1;
    double start, end, elapsed;

    arr = (int*)malloc(10000000 * sizeof(int));

    for(f = 0; f < 10000000; f++)
        arr[f] = f;
    
    GET_TIME(start);
    if(dfs(9999999, 0) != -1)
        printf("FOUND 101010\n");
    else
        printf("CAN'T FIND 101010\n");
    GET_TIME(end);
    printf("time elapsed: %lf\n", end - start);


    GET_TIME(start);
    if(dfs(10203040, 0) != -1)
        printf("FOUND 10203040\n");
    else
        printf("CAN'T FIND 10203040\n");
    GET_TIME(end);
    printf("time elapsed: %lf\n", end - start);

    GET_TIME(start);
    for(f = 0; f < 10000000; f++)
    {
        if(arr[f] == 9999999)
        {
            printf("FOUND 101010\n");
            break;
        }
    }
    GET_TIME(end);
    printf("time elapsed: %lf\n", end - start);

    return 0;
}

