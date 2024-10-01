#include <iostream>
#include "MyFunctions.hpp"
#include "MyClass.hpp"
using namespace std;

int main(void){
    string s;
    getline(cin,s);
    try{
        int result = expressionCalculate(s);
        cout << result;
    }
    catch(exception& e){
        cout << e.what();
    }
    return 0;
}