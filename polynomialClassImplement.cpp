#include "MyFunctions.hpp"
#include "MyClass.hpp"
using namespace std;

// 默认构造函数
Polynomial::Polynomial() {
    head = new PolyNode();  // 初始化多项式头节点
}

// 使用已有节点创建多项式
Polynomial::Polynomial(PolyNode *h) : head(h) {}

// 拷贝构造函数
Polynomial::Polynomial(const Polynomial &p) {
    head = new PolyNode(p.head->coefficient, p.head->exponent);  // 深拷贝头节点
    PolyNode *curr = p.head->next;  // 遍历源多项式的节点
    PolyNode *temp = head;  // 新多项式的当前节点
    while (curr != nullptr) {
        temp->next = new PolyNode(curr->coefficient, curr->exponent);  // 拷贝节点
        curr = curr->next;  // 移动到下一个节点
        temp = temp->next;  // 移动当前节点
    }
}

// 析构函数
Polynomial::~Polynomial() {
    clear();  // 清空多项式
    delete head;  // 删除头节点
}

// 赋值运算符重载
Polynomial &Polynomial::operator=(const Polynomial &p) {
    if (this != &p) {  // 自我赋值检查
        clear();  // 先清空当前多项式
        head = new PolyNode(p.head->coefficient, p.head->exponent);  // 拷贝头节点
        PolyNode *curr = p.head->next;  // 遍历源多项式的节点
        PolyNode *temp = head;  // 新多项式的当前节点
        while (curr != nullptr) {
            temp->next = new PolyNode(curr->coefficient, curr->exponent);  // 拷贝节点
            curr = curr->next;  // 移动到下一个节点
            temp = temp->next;  // 移动当前节点
        }
    }
    return *this;  // 返回当前对象的引用
}

// 复合多项式的加法
Polynomial Polynomial::operator+(const Polynomial &p) const {
    Polynomial result;  // 结果多项式
    PolyNode *curr1 = head->next;  // 当前多项式的节点
    PolyNode *curr2 = p.head->next;  // 参数多项式的节点

    // 遍历并相加同类项
    while (curr1 != nullptr && curr2 != nullptr) {
        if (curr1->exponent == curr2->exponent) {
            result.insert(curr1->coefficient + curr2->coefficient, curr1->exponent);  // 合并同类项
            curr1 = curr1->next;  // 移动到下一个节点
            curr2 = curr2->next;  // 移动到下一个节点
        } else if (curr1->exponent < curr2->exponent) {
            result.insert(curr2->coefficient, curr2->exponent);  // 插入更高次的项
            curr2 = curr2->next;  // 移动到下一个节点
        } else {
            result.insert(curr1->coefficient, curr1->exponent);  // 插入更高次的项
            curr1 = curr1->next;  // 移动到下一个节点
        }
    }

    // 将剩余的项插入结果
    while (curr1 != nullptr) {
        result.insert(curr1->coefficient, curr1->exponent);
        curr1 = curr1->next;
    }

    while (curr2 != nullptr) {
        result.insert(curr2->coefficient, curr2->exponent);
        curr2 = curr2->next;
    }

    return result;  // 返回结果多项式
}

// 复合多项式的减法
Polynomial Polynomial::operator-(const Polynomial &p) const {
    Polynomial result;  // 结果多项式
    PolyNode *curr1 = head->next;  // 当前多项式的节点
    PolyNode *curr2 = p.head->next;  // 参数多项式的节点

    // 遍历并相减同类项
    while (curr1 != nullptr && curr2 != nullptr) {
        if (curr1->exponent == curr2->exponent) {
            result.insert(curr1->coefficient - curr2->coefficient, curr1->exponent);  // 合并同类项
            curr1 = curr1->next;  // 移动到下一个节点
            curr2 = curr2->next;  // 移动到下一个节点
        } else if (curr1->exponent < curr2->exponent) {
            result.insert(-curr2->coefficient, curr2->exponent);  // 插入更高次的项（减去）
            curr2 = curr2->next;  // 移动到下一个节点
        } else {
            result.insert(curr1->coefficient, curr1->exponent);  // 插入更高次的项
            curr1 = curr1->next;  // 移动到下一个节点
        }
    }

    // 将剩余的项插入结果
    while (curr1 != nullptr) {
        result.insert(curr1->coefficient, curr1->exponent);
        curr1 = curr1->next;
    }

    while (curr2 != nullptr) {
        result.insert(-curr2->coefficient, curr2->exponent);  // 将参数多项式的剩余项作为负项插入
        curr2 = curr2->next;
    }

    return result;  // 返回结果多项式
}

// 插入新的项
void Polynomial::insert(double c, int e) {
    PolyNode *curr = head;

    // 寻找合适的位置插入新的项
    while (curr->next != nullptr && curr->next->exponent > e) {
        curr = curr->next;
    }

    // 插入新项或合并同类项
    if (curr->next == nullptr || curr->next->exponent < e) {
        curr->next = new PolyNode(c, e, curr->next);  // 创建新项
    } else {
        curr->next->coefficient += c;  // 合并同类项
    }
}

// 复合多项式的乘法
Polynomial Polynomial::operator*(const Polynomial &p) const {
    Polynomial result;  // 结果多项式
    PolyNode *curr1 = head->next;  // 当前多项式的节点

    // 遍历并相乘每一项
    while (curr1 != nullptr) {
        PolyNode *curr2 = p.head->next;  // 参数多项式的节点
        while (curr2 != nullptr) {
            int new_exponent = curr1->exponent + curr2->exponent;  // 新的指数
            double new_coefficient = curr1->coefficient * curr2->coefficient;  // 新的系数
            result.insert(new_coefficient, new_exponent);  // 插入新项
            curr2 = curr2->next;  // 移动到下一个节点
        }
        curr1 = curr1->next;  // 移动到下一个节点
    }

    return result;  // 返回结果多项式
}

// 多项式乘以常数
Polynomial Polynomial::operator*(double k) const {
    Polynomial result;  // 结果多项式
    PolyNode *curr = head->next;  // 当前多项式的节点

    // 遍历并乘以常数
    while (curr != nullptr) {
        result.insert(curr->coefficient * k, curr->exponent);
        curr = curr->next;  // 移动到下一个节点
    }

    return result;  // 返回结果多项式
}

// 清空多项式
void Polynomial::clear() {
    PolyNode *curr = head->next;  // 当前多项式的节点
    while (curr != nullptr) {
        PolyNode *temp = curr;  // 临时节点保存当前节点
        curr = curr->next;  // 移动到下一个节点
        delete temp;  // 删除当前节点
    }
    head->next = nullptr;  // 清空头节点的下一指针
}

// 输入流重载，输入多项式
istream &operator>>(istream &i, Polynomial &p) {
    string s;
    do {
        cout << endl << endl << "请输入多项式（请按要求正确输入多项式）" << endl;
        cout << "请输入对应指令：\n";
        cout << "1.输入\"Mode1\": 通过输入系数和指数创造或添加多项式\n";
        cout << "2.输入\"Mode2\": 通过输入多项式的形式创造或添加多项式\n";
        cout << "3.输入\"Restart\": 清空当前创建的多项式并重新输入\n";
        cout << "4.输入\"End\": 结束输入\n";

        i.clear();  // 清理输入流状态
        getline(i, s);  // 读取用户输入

        while (s != "End" && s != "Mode1" && s != "Mode2" && s != "Restart") {
            cout << "输入无效，请重新输入喵：\n";
            i.clear();
            getline(i, s);
        }

        // “Mode1”: 通过系数和指数添加多项式
        if (s == "Mode1") {
            string curr;
            while (true) {
                cout << "目前输入模式为Mode1，通过输入系数和指数创造或添加多项式\n";
                cout << "目前的多项式为：\n";
                cout << p << endl << endl;
                cout << "是否需要退出当前模式？如是请输入\"Exit\"，否则请输入其他任意字符\n";
                curr.clear();
                getline(i, curr);
                
                // 退出模式
                if (curr == "Exit") {
                    cout << "已退出Mode1\n";
                    cout << "目前的多项式为：\n";
                    cout << p << endl << endl;
                    break;
                } else {
                    double c;  // 系数
                    int e;  // 指数
                    
                    cout << "请输入你要添加的项的系数：";
                    cin >> c;
                    cin.clear();  // 清除输入流状态
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    cout << "请输入你要添加的项的指数：";
                    cin >> e;
                    cin.clear();  // 清除输入流状态
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    p.insert(c, e);  // 插入项
                    cout << "已成功添加项!" << endl;
                    cout << "目前的多项式为：\n";
                    cout << p << endl << endl;
                }
            }
        }
        
        // “Mode2”: 通过多项式字符串添加多项式
        else if (s == "Mode2") {
            string curr;
            while (true) {
                cout << "目前输入模式为Mode2，通过输入多项式的形式创造或添加多项式\n";
                cout << "目前的多项式为：\n";
                cout << p << endl << endl;
                cout << "是否需要退出当前模式？如是请输入\"Exit\"，否则请输入其他任意字符\n";
                curr.clear();
                getline(i, curr);
                
                // 退出模式
                if (curr == "Exit") {
                    cout << "已退出Mode2\n";
                    cout << "目前的多项式为：\n";
                    cout << p << endl << endl;
                    break;
                }
                
                cout << "请输入多项式的形式，如Ax^a+Bx^b+Cx^c，其中A,B,C为系数，a,b,c为指数\n";
                cout << "请根据上述形式输入想添加的多项式：\n";
                string cur;
                getline(i, cur);  // 读取多项式输入
                int pos = 0;
                int nextFind = pos;
                
                // 继续提取多项式项
                while (pos < cur.length()) {
                    int nextPos = cur.find_first_of("+-", nextFind);
                    string term;
                    
                    if (nextPos > 0 && cur[nextPos-1] == '^'){
                        nextFind = nextPos + 1;
                        continue;
                    }   // 处理指数为负数的情况
                    if (nextPos == string::npos) {
                        term = cur.substr(pos);
                        pos = cur.length();
                    } else if (nextFind == nextPos) {
                        nextPos = cur.find_first_of("+-", nextFind + 1);
                        if (nextPos > 0 && cur[nextPos-1] == '^'){
                            nextFind = nextPos + 1;
                            continue;
                        }   // 处理指数为负数的情况
                        if (nextPos == string::npos) {
                            term = cur.substr(pos);
                            pos = cur.length();
                        } else {
                            term = cur.substr(pos, nextPos - pos);
                            pos = nextPos;
                            nextFind = pos + 1;
                        }
                    } else {
                        term = cur.substr(pos, nextPos - pos);
                        pos = nextPos;
                        nextFind = pos + 1;
                    }

                    // 处理项的符号
                    int sign = 1;
                    if (term[0] == '-') {
                        sign = -1;  // 负号
                        term = term.substr(1);  // 去除负号
                    } else if (term[0] == '+') {
                        term = term.substr(1);  // 去除正号
                    }

                    double coef = 1;  // 系数
                    int exp = 0;  // 指数
                    int xPos = term.find('x');  // 查找 'x' 的位置

                    if (xPos != string::npos) {  // 存在 'x'
                        if (xPos > 0) {
                            coef = stod(term.substr(0, xPos)) * sign;  // 提取系数
                        } else {
                            coef = sign;  // 当负号为前缀时直接赋值
                        }

                        int caretPos = term.find('^', xPos);  // 查找 '^' 的位置
                        if (caretPos != string::npos) {
                            string expStr = term.substr(caretPos + 1);  // 提取指数
                            exp = stoi(expStr);  // 转换为整型
                        } else {
                            exp = 1;  // 默认指数为1
                        }
                    } else {  // 常数项
                        coef = stod(term) * sign;  // 提取系数
                        exp = 0;  // 常数项的指数为0
                    }

                    p.insert(coef, exp);  // 插入项
                }

                cout << "已成功添加项!" << endl;
                cout << "目前的多项式为：\n";
                cout << p << endl << endl;
            }
        }
        
        // 清空多项式
        else if (s == "Restart") {
            p.clear();  // 清空多项式
            cout << "已清空当前创建的多项式！\n" << endl;
        }
        
        // 结束输入
        else if (s == "End") {
            cout << "已结束输入！\n" << endl << endl;
            break;
        }
    } while (s != "End");

    return i;  // 返回输入流
}

// 输出流重载，输出多项式
ostream &operator<<(ostream &o, const Polynomial &p) {
    PolyNode *curr = p.head->next;  // 当前多项式的节点
    bool isFirst = true;  // 用于判断是否为第一项

    // 遍历多项式并输出
    while (curr != nullptr) {
        if (curr->coefficient != 0) {  // 非零系数项
            if (!isFirst) {
                if (curr->coefficient > 0) {
                    o << "+";  // 输出正号
                }
            }
            if (curr->exponent != 0) {  // 不为常数项
                if (curr->coefficient != 1 && curr->coefficient != -1) {
                    o << curr->coefficient;  // 输出系数
                } else if (curr->coefficient == -1) {
                    o << "-";  // 输出负号
                }
                o << "x";  // 输出 'x'
                if (curr->exponent != 1) {
                    o << "^" << curr->exponent;  // 输出指数
                }
            } else {
                o << curr->coefficient;  // 常数项输出
            }
            isFirst = false;  // 第一个项已输出
        }
        curr = curr->next;  // 移动到下一个节点
    }

    if (isFirst) {
        o << "0";  // 如果没有项，输出0
    }
    return o;  // 返回输出流
}

// 计算多项式在给定 x 的值
double Polynomial::calculate(double x) const {
    double result = 0;  // 存储计算结果
    PolyNode *curr = head->next;  // 当前多项式的节点

    // 遍历多项式并计算结果
    while (curr != nullptr) {
        if (curr->exponent >= 0) result += curr->coefficient * pow(x, curr->exponent);  // 累加每一项的结果
        else result += curr->coefficient / pow(x, -curr->exponent);  // 负指数项需要除以 x 的绝对值
        curr = curr->next;  // 移动到下一个节点
    }
    return result;  // 返回计算结果
}

// 求多项式的导数
Polynomial Polynomial::derivative() const {
    Polynomial result;  // 结果多项式
    PolyNode *curr = head->next;  // 当前多项式的节点

    // 遍历多项式并计算导数
    while (curr != nullptr) {
        if (curr->exponent != 0) {
            result.insert(curr->exponent * curr->coefficient, curr->exponent - 1);  // 插入导数项
        }
        curr = curr->next;  // 移动到下一个节点
    }
    return result;  // 返回导数多项式
}
