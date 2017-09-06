#include <stdio.h>

int main()
{

#if defined(LIN) || defined(LIN64)
    printf("LIN OR LIN64 IS DEFINED\n");
#else
    printf("LIN NOT DEFINED\n");
#endif

#if defined(__MACH__) && defined(__APPLE__)
    printf("MACH AND APPLE IS DEFINED\n");
#endif
       
}

