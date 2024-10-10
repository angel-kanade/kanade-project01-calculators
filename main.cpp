#include <iostream>
#include "MyFunctions.hpp"
#include "MyClass.hpp"
using namespace std;

int main(void) {
    string choice;

    while (true) {
        cout << "本程序提供两个计算器功能：稀疏一元多项式计算器和表达式求值计算器。" << endl << endl;
        cout << "输入\"1\"选择稀疏一元多项式计算器；\n输入\"2\"选择表达式求值计算器；" << endl;
        cout << "输入\"0\"退出程序。" << endl;
        cout << "请输入选择：";
        
        cin.clear(); // 清除输入缓冲区
        getline(cin, choice);

        if (choice == "1") {
            runningPolynomialCalculator();
        }
        else if (choice == "2") {
            runningExpressionCalculator();
        }
        else if (choice == "0") {
            cout << "感谢使用，下次再见喵！" << endl;
            break; // 退出循环
        }
        else {
            cout << endl << endl << "输入错误，请参照指令重新输入喵。" << endl;
        }
    }

    system("pause");
    return 0;
}
