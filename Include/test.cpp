#include <iostream>
#include <memory>
#include <map>
#include <vector>
using namespace std;

void s()
{

    throw 90;
    cout << "How about we do\n";
}

int main()
{
    try
    {
        s();
    }
    catch (int e)
    {
        std::cout << e;
    }

    return 0;
}
