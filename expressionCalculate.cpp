#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <stdexcept>
#include <cmath>
using namespace std;

/*
    根据题意：
    从终端输入的表达式已是“不含变量”的“整数”表达式。
    思路：
        采用逆波兰表达式方法来实现表达式求值。
		单目减符号用"@"表示，运算符优先级按从左到右的顺序。
    加分：
        乘方、单目减（负数）、赋值等运算的实现。
*/

// 表达式计算函数，接受一个字符串格式的数学表达式
int expressionCalculate(string s) {
    stack<char> opStk;           // 运算符栈
    vector<string> expression;    // 存储逆波兰表达式
    stack<int> numStk;            // 数字栈

    // 遍历输入字符串的每个字符
    for (int i = 0; i < s.size(); ++i) {
        // 处理乘法、除法和取模运算
        if (s[i] == '*' || s[i] == '/' || s[i] == '%') {
            // 将符合条件的运算符从栈中弹出并存入逆波兰表达式
            while (!opStk.empty() && !(opStk.top() == '+' || opStk.top() == '-' || opStk.top() == '(')) {
                char curr = opStk.top();
                opStk.pop();
                expression.push_back(string(1, curr));
            }
            opStk.push(s[i]);  // 将运算符压入栈中
        } 
        // 忽略空格
        else if (s[i] == ' ')  continue;

        // 处理加法运算
        else if (s[i] == '+') {
            while (!opStk.empty() && !(opStk.top() == '(')) {
                char curr = opStk.top();
                opStk.pop();
                expression.push_back(string(1, curr));  // 弹出栈中的运算符
            }
            opStk.push(s[i]);  // 加法运算符入栈
        } 
        // 处理左括号
        else if (s[i] == '(') {
            opStk.push(s[i]);  // 左括号入栈
        } 
        // 处理右括号
        else if (s[i] == ')') {
            while (opStk.top() != '(') {  // 弹出直到遇到左括号
                char curr = opStk.top();
                opStk.pop();
                expression.push_back(string(1, curr));
            }
            opStk.pop();  // 弹出左括号
        } 
        // 处理乘方运算
        else if (s[i] == '^') {
            while (!opStk.empty() && !(opStk.top() == '+' || opStk.top() == '-' || opStk.top() == '@' ||
                                         opStk.top() == '*' || opStk.top() == '/' || opStk.top() == '%' || 
                                         opStk.top() == '(')) {
                char curr = opStk.top();
                opStk.pop();
                expression.push_back(string(1, curr));  // 弹出栈中的运算符
            }
            opStk.push(s[i]);  // 乘方运算符入栈
        } 
        // 处理单目减法（负数）
        else if (s[i] == '-') {
            int curIndex = i;  // 记录当前字符的索引
            i--;  // 向左移动
            while (i >= 0 && s[i] == ' ') {
                i--;  // 跳过空格
            }
            // 如果是数字或右括号，正常处理减法
            if (isdigit(s[i]) || s[i] == ')') {
                while (!opStk.empty() && !(opStk.top() == '(')) {
                    char curr = opStk.top();
                    opStk.pop();
                    expression.push_back(string(1, curr));  // 弹出栈中的运算符
                }
                opStk.push(s[curIndex]);  // 将减法运算符入栈
            }
            // 如果是负号，标记为单目负号
            else if (i < 0 || (!isdigit(s[i]) && s[i] != ')')) {
                while (!opStk.empty() && !(opStk.top() == '+' || opStk.top() == '-' || 
                                             opStk.top() == '*' || opStk.top() == '/' || 
                                             opStk.top() == '%' || opStk.top() == '(')) {
                    char curr = opStk.top();
                    opStk.pop();
                    expression.push_back(string(1, curr));  // 弹出栈中的运算符
                }
                opStk.push('@');  // 用‘@’符号表示单目负号
            }                        
            i = curIndex;  // 还原索引
        }
        // 处理数字
        else {
            string curr;
            while (s[i] >= '0' && s[i] <= '9') {
                curr.push_back(s[i]);  // 拼接数字
                i++;
                if (i == s.size()) break;  // 遇到字符串末尾
            }
            expression.push_back(curr);  // 将数字插入逆波兰表达式
            i--;  // 修正索引
        }
    }

    // 将运算符栈中剩余的运算符全部加入逆波兰表达式
    while (!opStk.empty()) {
        string curr(1, opStk.top());
        opStk.pop();
        expression.push_back(curr);
    }

    // 开始根据逆波兰表达式计算结果
    for (auto &x : expression) {
        if (x[0] >= '0' && x[0] <= '9') {
            numStk.push(stoi(x));  // 将数字转换为整型并入栈
        }
        // 处理单目负号
        else if (x[0] == '@') {
            int top = numStk.top();  // 取栈顶元素
            numStk.pop();
            numStk.push(-top);  // 将其反转后入栈
        } 
        // 处理运算符
        else {
            int ret = -1;  // 存放运算结果
            int right = numStk.top();  // 取出右操作数
            numStk.pop();
            int left = numStk.top();  // 取出左操作数
            numStk.pop();

            // 根据运算符进行相应的运算
            if (x[0] == '+') ret = left + right;
            else if (x[0] == '-') ret = left - right;
            else if (x[0] == '*') ret = left * right;
            else if (x[0] == '/') {
                if (right) ret = left / right;  // 确保右操作数不为0
                else throw runtime_error("0不能作为除数喵");  // 抛出异常
            }
            else if (x[0] == '%') {
                if (right) ret = left % right;  // 确保右操作数不为0
                else throw runtime_error("0不能作为除数喵");  // 抛出异常
            }
            else { 
                if (right >= 0) ret = (int)pow(left, (double)right);  // 计算乘方
                else throw runtime_error("小于0的指数不支持喵");  // 抛出异常
            }
            numStk.push(ret);  // 将结果入栈
        }
    }
    
    return numStk.top();  // 返回结果栈顶元素
}
