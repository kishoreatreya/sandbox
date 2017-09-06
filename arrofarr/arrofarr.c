#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int **arrglobal = NULL;
static int ***arrpd = NULL;

#define BARRIER 8

#define GET_INT(x,y) ((x >= BARRIER) ? \
                      arrpd[x-BARRIER][y] : \
                      arrglobal[x])

int main(void)
{
    int i = 0;
    int j = 0;
    int* f = NULL;


    // allocate space for the global array of pointers
    arrglobal = malloc(sizeof(int*) * 8);

    // allocate space for the pd array of pointers to arrays of pointers
    arrpd = malloc(sizeof(int**) * 2);

    // Populate global
    for(i = 0; i < 8; i++)
    {
        f = (int*)malloc(sizeof(int));
        *f = i;
        arrglobal[i] = f;
    }

    // Populate pd
    for(i = 0; i < 2; i++)
    {
        arrpd[i] = malloc(sizeof(int*) * 8);
        for(j = 0; j < 8; j++)
        {
            f = (int*)malloc(sizeof(int));
            *f = (i * 8) + j + 100;
            arrpd[i][j] = f;
        }
    }

    // print
    for(i = 0; i < 8; i++)
    {
        printf("arrglobal[%d] = %p val: %d\n", i, arrglobal[i], *arrglobal[i]);
    }

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 8; j++)
        {
            printf("arrpd[%d][%d] = %p val: %d\n", i, j, arrpd[i][j], *arrpd[i][j]);
        }
    }
    

    // Fetch arrglobal 4
    int* tmp = GET_INT(4,0);

    printf("tmp = %d\n", *tmp);

    // fetch arrpd 1, 5
    //
    tmp = GET_INT(9, 5);

    printf("tmp pd = %d\n", *tmp);



/*
    for(i = 0; i < 8; i++)
    {
        f = (int*)malloc(sizeof(int));
        *f = i;
        arrglobal[i] = f;
    }

    for(i = 0; i < 8; i++)
    {
        printf("arrglobal[%d] val: %d\n", i, *arrglobal[i]);
    }

    for(i = 0; i < 8; i++)
    {
        free(arrglobal[i]);
    }
    
    for(i = 0; i < 2; i++)
    {
        f = (int*)malloc(sizeof(int) * 64);
        arrpd[i] = f;

        for(j = 0; j < 64; j++)
        {
            f[j] = (i * 64) + j;
        }
    }

    for(i = 0 ; i < 2; i++)
    {
        for(j = 0; j < 64; j++)
        {
            printf("arrpd[%d][%d] = %d\n", i, j, arrpd[i][j]);
        }
    }
*/    
    return 0;
}

