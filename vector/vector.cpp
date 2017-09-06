#include <iostream>
#include <vector>

using namespace std;


int main()
{
    vector<int> iv;
    vector<int> ev;

    for(int i = 0; i < 10; i++)
    {
        iv.push_back(i);
    }

    for(int i = 0; i < iv.size(); i++)
    {
        cout << "iv[" << i << "] = " << iv[i] << endl;
    }

    // concat an empty vector
    iv.insert(iv.end(), ev.begin(), ev.end());

    for(int i = 0; i < iv.size(); i++)
    {
        cout << "iv+ev[" << i << "] = " << iv[i] << endl;
    }

    return 0;
}
