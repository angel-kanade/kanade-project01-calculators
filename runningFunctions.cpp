#include <iostream>
#include "MyClass.hpp"
#include "MyFunctions.hpp"
using namespace std;

void runningPolynomialCalculator() {
    while (true) {
        cout << endl << endl << "已选择多项式计算器" << endl;
        cout << "该计算器提供以下功能：" << endl;
        cout << "输入\"1\"计算多项式在x点的值；" << endl;
        cout << "输入\"2\"计算k倍多项式；" << endl;
        cout << "输入\"3\"计算多项式的导数；" << endl;
        cout << "输入\"4\"计算两个多项式的和；" << endl;
        cout << "输入\"5\"计算两个多项式的差；" << endl;
        cout << "输入\"6\"计算两个多项式的积；" << endl;
        cout << "输入\"Exit\"退出该计算器。" << endl;
        cout << "请输入你的指令：";
        
        string input;
        cin.clear();
        getline(cin, input);
        
        if (input == "1") {
            Polynomial p;
            cin >> p;
            cout << "请输入x的值（请输入一个实数）：";
            double x;
            cin >> x;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            try{
                double ret = p.calculate(x);
                cout << "多项式" << p << "在" << x << "处的值为：" << endl << ret << endl << endl;
            }
            catch(const std::invalid_argument& e){
                cout << e.what() << endl<< endl;
            }
        }
        else if (input == "2") {
            Polynomial p;
            cin >> p;
            cout << "请输入k的值（请输入一个实数）：";
            double k;
            cin >> k;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "多项式" << p << "的" << k << "倍为：" << endl << p*k << endl << endl;
        }
        else if (input == "3") {
            Polynomial p;
            cin >> p;
            cout << "多项式" << p << "的导数为：" << endl << p.derivative() << endl << endl;
        }
        else if (input == "4") {
            Polynomial p1, p2;
            cout << "请输入第一个多项式（请按要求正确输入多项式）" << endl;
            cin >> p1;
            cout << "请输入第二个多项式（请按要求正确输入多项式）" << endl;
            cin >> p2;
            cout << "多项式" << p1 << "和" << p2 << "的和为：" << endl << p1 + p2 << endl << endl;
        }
        else if (input == "5") {
            Polynomial p1, p2;
            cout << "请输入第一个多项式（请按要求正确输入多项式）" << endl;
            cin >> p1;
            cout << "请输入第二个多项式（请按要求正确输入多项式）" << endl;
            cin >> p2;
            cout << "多项式" << p1 << "和" << p2 << "的差为：" << endl << p1 - p2 << endl << endl;
        }
        else if (input == "6") {
            Polynomial p1, p2;
            cout << "请输入第一个多项式（请按要求正确输入多项式）" << endl;
            cin >> p1;
            cout << "请输入第二个多项式（请按要求正确输入多项式）" << endl;
            cin >> p2;
            cout << "多项式" << p1 << "和" << p2 << "的积为：" << endl << p1 * p2 << endl << endl;
        }
        else if (input == "Exit") {
            cout << "已退出该计算器，欢迎下次再来喵！" << endl << endl << endl;
            return; // 返回到 main 函数
        }
        else {
            cout << "输入指令有误，请重新输入喵！" << endl << endl;
        }
    }
}

void runningExpressionCalculator(){
    while (true) {
        cout << endl << endl << "已选择表达式计算器" << endl;
        cout << "该计算器提供以下功能：" << endl;
        cout << "输入\"1\"计算表达式的值；" << endl;
        cout << "输入\"Exit\"退出该计算器。" << endl;
        cout << "请输入你的指令：";
        
        string input;
        getline(cin, input);
        
        if (input == "1") {
            string expression;
            cout << "请输入表达式（以字符序列的形式输入语法正确的、不含变量的整数表达式）" << endl;
            getline(cin, expression);
            cout << "表达式" << expression << "的值为：" << endl << expressionCalculate(expression);
        }
        else if (input == "Exit") {
            cout << "已退出该计算器，欢迎下次再来喵！" << endl << endl << endl;
            return; // 返回到 main 函数
        }
        else {
            cout << "输入指令有误，请重新输入喵！" << endl << endl;
        }
    }
}
