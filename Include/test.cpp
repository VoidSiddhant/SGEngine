#include<iostream>
#include <memory>
#include <map>
using namespace std;

int main()
{
    int a = 10;
    int* ap = new int{10};
    map<std::string,int*> _map;
    _map.insert(map<std::string,int*>::value_type("Value",ap));
    cout<<*_map["Value"];
    return 0;
}