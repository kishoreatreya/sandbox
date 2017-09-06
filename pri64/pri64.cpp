#include <iostream>
#include <stdint.h>
#include <inttypes.h>

// This is the c++ implementation of standard print macros
//

int main(void)
{
    uint64_t x = 0x1234567890;  // 40 bits

    printf("printing x: %" PRIu64 "\n", x);

    return 0;
}

