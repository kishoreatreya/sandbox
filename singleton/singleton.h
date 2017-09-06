#include <iostream>

using namespace std;

class singleton
{
protected:
    singleton() {}
    ~singleton() {}

public:
    void print() { cout << "helloworld" << endl; }

    static singleton* instance();

private:
    static singleton* mInstance;

};


