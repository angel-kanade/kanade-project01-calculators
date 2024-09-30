#include <iostream>
#include "MyFunctions.hpp"
using namespace std;

int main(void){
    string s;
    getline(cin,s);
    int ret = -1;
    if (expressionCalculate(s,ret)) cout << ret;
    else cout << "ERROR";
    return 0;
}