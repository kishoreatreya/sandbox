#include <iostream>
#include <stdint.h>

using namespace std;

class foo
{
public:
    void print(uint32_t bar) { cout << "Reached uint32_t print: " << bar << endl; }
    void print(uint64_t bar, uint32_t foo) { cout << "Reached uint64_t print: " << bar << endl; }
};

