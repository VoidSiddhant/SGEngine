#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include "SGUtil.h"
using namespace std;

void printList(const char *str)
{
    cout << str;
}

int main()
{
   /* ifstream file("../Shader/vs", ios_base::ate);
    SG_UINT size = file.tellg();
    char *s = new char[size];
    cout << "File length : " << sizeof(s) << endl;
    file.seekg(0, ios_base::beg);
    file.read(s, size);
    cout << s; */
    int s;
    cin>>s;
    char buffer[s];
    buffer[0] = 'd';
    cout<<buffer;
    return 0;
}