#include <stdio.h>
#include <stdint.h>


typedef struct foobar
{
    uint64_t a;
    uint64_t b;
} foobar;

foobar fuckthisshit = 
{
    UINT64_C(0xFFFFFFFFABCD),
    UINT64_C(0xAAAAAAAAFEDC),
};

int main(void)
{

    printf("fuckthisshit.a: %llx\n", fuckthisshit.a);
    printf("fuckthisshit.b: %llx\n", fuckthisshit.b);
    
    return 0;

}




