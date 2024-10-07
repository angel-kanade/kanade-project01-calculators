#include <iostream>
#include <string>
#include "MyFunctions.hpp"
#include "MyClass.hpp"
using namespace std;

/*
	依据题意
	从终端输入的表达式已是“正确”的不含变量的“整数”表达式
	思路：
		转化为逆波兰表达式实现表达式求值
	加分：
		乘方 单目减（负数） 赋值等运算的实现
*/
int expressionCalculate(string s){
	stack<char> opStk;
	vector<string> expression;
	stack<int> numStk;
	for (int i = 0; i < s.size(); ++i){
		if (s[i] == '*' || s[i] == '/' || s[i] == '%'){
			while (!opStk.empty() && !(opStk.top() == '+' || opStk.top() == '-' || opStk.top() == '(')){
				char curr = opStk.top();
				opStk.pop();
				expression.push_back(string(1, curr));
			}
			opStk.push(s[i]);
		}
		else if (s[i] == ' ')  continue;
		else if (s[i] == '+'){
			while (!opStk.empty() && !(opStk.top() == '(')){
				char curr = opStk.top();
				opStk.pop();
				expression.push_back(string(1, curr));
			}
			opStk.push(s[i]);
		}
		else if (s[i] == '('){
			opStk.push(s[i]);
		}
		else if (s[i] == ')'){
			while (opStk.top() != '('){
				char curr = opStk.top();
				opStk.pop();
				expression.push_back(string(1,curr));
			}
			opStk.pop();
		}
		else if (s[i] == '^'){
			while (!opStk.empty() && !(opStk.top() == '+'||opStk.top() == '-'|| opStk.top() == '@' ||
			opStk.top() == '*'||opStk.top() == '/'||opStk.top() == '%' ||opStk.top() == '(')){
				char curr = opStk.top();
				opStk.pop();
				expression.push_back(string(1,curr));
			}
			opStk.push(s[i]);
		}
		else if (s[i] == '-'){
			int curIndex = i;
			i--;
			while (i >= 0 && s[i] == ' '){
				i--;
			}
			if (isdigit(s[i])||s[i] == ')'){
				while (!opStk.empty() && !(opStk.top() == '(')){
					char curr = opStk.top();
					opStk.pop();
					expression.push_back(string(1, curr));
				}
				opStk.push(s[curIndex]);
			}
			else if (i < 0 || (!isdigit(s[i])&&s[i] != ')')){
				while (!opStk.empty() && !(opStk.top() == '+'||opStk.top() == '-' ||
				opStk.top() == '*'||opStk.top() == '/'||opStk.top() == '%' ||opStk.top() == '(')){
					char curr = opStk.top();
					opStk.pop();
					expression.push_back(string(1,curr));
				}
				opStk.push('@');	//用‘@’符号表示单目负号
			}						
			i = curIndex;
		}
		else{
			string curr;
			while (s[i] >= '0' && s[i] <= '9'){
				curr.push_back(s[i]);
				i++;
				if (i == s.size())  break;
			}
			expression.push_back(curr);
			i--;
		}
	}
	while (!opStk.empty()){
		string curr(1, opStk.top());
		opStk.pop();
		expression.push_back(curr);
	}
	for (auto &x : expression){
		if (x[0] >= '0' && x[0] <= '9'){
			numStk.push(stoi(x));
		}
		else if (x[0] == '@'){
			int top = numStk.top();
			numStk.pop();
			numStk.push(-top);
		}
		else{
			int ret = -1;
			int right = numStk.top();
			numStk.pop();
			int left = numStk.top();
			numStk.pop();
			if (x[0] == '+')  ret = left + right;
			else if (x[0] == '-')  ret = left - right;
			else if (x[0] == '*')  ret = left * right;
			else if (x[0] == '/'){
				if (right) ret = left / right;
				else throw runtime_error("0不能作为除数喵");
			}
			else if (x[0] == '%'){
				if (right) ret = left % right;
				else throw runtime_error("0不能作为除数喵");
			}
			else { 
				if (right >= 0) ret = (int)pow(left,(double)right);
				else throw runtime_error("小于0的指数不支持喵");
			}
			numStk.push(ret);
		}
	}
	return numStk.top();
}