#include <vector>
#include <iostream>



int main(void)
{
    std::vector<int> intVec;
    
    auto it = intVec.begin();
    
    // Insert 10 at 0
    intVec.emplace(it+0, 10);
    
    // Insert 20 at 5
    intVec.emplace(it+5, 20);
    
    // print
    
    for(auto &i: intVec)
    {
        std::cout << i << std::endl;
    }
    
    return 0;
}