#include "MyFunctions.hpp"
#include "MyClass.hpp"
using namespace std;

Polynomial::Polynomial(){
    head = new PolyNode();
}

Polynomial::Polynomial(PolyNode* h):head(h){}

Polynomial::Polynomial(const Polynomial& p){
    head = new PolyNode(p.head->coefficient, p.head->exponent);
    PolyNode* curr = p.head->next;
    PolyNode* temp = head;
    while(curr!= nullptr){
        temp->next = new PolyNode(curr->coefficient, curr->exponent);
        curr = curr->next;
        temp = temp->next;
    }
}

Polynomial::~Polynomial(){
    PolyNode* curr = head;
    while(curr!= nullptr){
        PolyNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

Polynomial& Polynomial::operator=(const Polynomial& p){
    if (head != p.head){
        PolyNode* curr = head;
        while(curr!= nullptr){
            PolyNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = new PolyNode(p.head->coefficient, p.head->exponent);
        curr = p.head->next;
        PolyNode* temp = head;
        while(curr!= nullptr){
            temp->next = new PolyNode(curr->coefficient, curr->exponent);
            curr = curr->next;
            temp = temp->next;
        }
    }
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial& p) const{
    Polynomial result;
    PolyNode* curr1 = head->next;
    PolyNode* curr2 = p.head->next;
    PolyNode* temp = result.head;
    while(curr1!= nullptr && curr2!= nullptr){
        if(curr1->exponent == curr2->exponent){
            temp->next = new PolyNode(curr1->coefficient + curr2->coefficient, curr1->exponent);
            curr1 = curr1->next;
            curr2 = curr2->next;
            temp = temp->next;
        }
        else if(curr1->exponent < curr2->exponent){
            temp->next = new PolyNode(curr2->coefficient, curr2->exponent);
            curr2 = curr2->next;
            temp = temp->next;
        }
        else{
            temp->next = new PolyNode(curr1->coefficient, curr1->exponent);
            curr1 = curr1->next;
            temp = temp->next;
        }
    }
    while(curr1!= nullptr){
        temp->next = new PolyNode(curr1->coefficient, curr1->exponent);
        curr1 = curr1->next;
        temp = temp->next;
    }
    while(curr2!= nullptr){
        temp->next = new PolyNode(curr2->coefficient, curr2->exponent);
        curr2 = curr2->next;
        temp = temp->next;
    }
    return result;
}
Polynomial Polynomial::operator-(const Polynomial& p) const{
    Polynomial result;
    PolyNode* curr1 = head->next;
    PolyNode* curr2 = p.head->next;
    PolyNode* temp = result.head;
    while(curr1!= nullptr && curr2!= nullptr){
        if(curr1->exponent == curr2->exponent){
            temp->next = new PolyNode(curr1->coefficient - curr2->coefficient, curr1->exponent);
            curr1 = curr1->next;
            curr2 = curr2->next;
            temp = temp->next;
        }
        else if(curr1->exponent < curr2->exponent){
            temp->next = new PolyNode(-curr2->coefficient, curr2->exponent);
            curr2 = curr2->next;
            temp = temp->next;
        }
        else{
            temp->next = new PolyNode(curr1->coefficient, curr1->exponent);
            curr1 = curr1->next;
            temp = temp->next;
        }
    }
    while(curr1!= nullptr){
        temp->next = new PolyNode(curr1->coefficient, curr1->exponent);
        curr1 = curr1->next;
        temp = temp->next;
    }
    while(curr2!= nullptr){
        temp->next = new PolyNode(-curr2->coefficient, curr2->exponent);
        curr2 = curr2->next;
        temp = temp->next;
    }
    return result;
}

void Polynomial::Insert(int c, int e){
    PolyNode* curr = head;
    while(curr->next != nullptr && curr->next->exponent < e){
        curr = curr->next;
    }
    if(curr->next == nullptr || curr->next->exponent > e){
        curr->next = new PolyNode(c, e);
    }
    else{
        curr->next->coefficient = c;
    }
}

Polynomial Polynomial::operator*(const Polynomial& p) const{
    Polynomial result;
    PolyNode* curr1 = head->next;
    PolyNode* curr2 = p.head->next;
    while(curr1 != nullptr){
        curr2 = p.head->next;
        while(curr2 != nullptr){
            int new_exponent = curr1->exponent + curr2->exponent;
            int new_coefficient = curr1->coefficient * curr2->coefficient;
            result.Insert(new_coefficient, new_exponent);
            curr2 = curr2->next;
        }
        curr1 = curr1->next;
    }
    return result;
}

Polynomial Polynomial::operator*(int k)const{
    Polynomial result;
    PolyNode* curr = head->next;
    while(curr != nullptr){
        result.Insert(curr->coefficient * k, curr->exponent);
        curr = curr->next;
    }
    return result;
}

void Polynomial::clear(){
    PolyNode* curr = head->next;
    while(curr != nullptr){
        PolyNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head->next = nullptr;
}

istream& operator>>(istream& i, Polynomial& p){
    string s;
    do{
        cout << "请输入对应指令：\n";
        cout << "1.输入\"Mode1\": 通过输入系数和指数创造或添加多项式\n";
        cout << "2.输入\"Mode2\": 通过输入多项式的形式创造或添加多项式\n";
        cout << "3.输入\"Restart\": 清空当前创建的多项式并重新输入\n";
        cout << "4.输入\"End\"：结束输入\n";
        getline(i,s);
        while(s != "End" && s != "Mode1" && s != "Mode2" && s != "Restart"){
            cout << "输入无效，请重新输入喵：\n";
            getline(i,s);
        }
        if(s == "Mode1"){
            while(true){
                cout << "目前输入模式为Mode1，通过输入系数和指数创造或添加多项式\n";
                cout << "是否需要退出当前模式？如是请输入\"Exit\"，否则请输入\"Continue\"\n";
                string curr;
                getline(i,curr);
                if (curr == "Exit"){
                    cout << "已退出Mode1\n";
                    cout << "目前的多项式为：\n";
                    cout << p;
                    break;
                }
                else{
                    cout << "请输入你要添加的项的系数：";
                    int c;
                    cin >> c;
                    int e;
                    cout << "请输入你要添加的项的指数：";
                    cin >> e;
                    p.Insert(c, e);
                    cout << "已成功添加项!" << endl;
                    cout << "目前的多项式为：\n";
                    cout << p;
                }
            }
        }
        else if(s == "Mode2"){
            while(true){
                cout << "目前输入模式为Mode2，通过输入多项式的形式创造或添加多项式\n";
                cout << "是否需要退出当前模式？如是请输入\"Exit\"，否则请输入\"Continue\"\n";
                string curr;
                getline(i,curr);
                if (curr == "Exit"){
                    cout << "已退出Mode2\n";
                    cout << "目前的多项式为：\n";
                    cout << p;
                    break;
                }
                cout << "请输入多项式的形式，如Ax^a+Bx^b+Cx^c，其中A,B,C为系数，a,b,c为指数\n";
                cout << "请根据上述形式输入想添加的多项式：\n";
                string cur;
                getline(i,cur);
                int pos = 0;
                while (pos < cur.length()){
                    int nextPos = cur.find_first_of("+-", pos);
                    string term;
                    if (nextPos == string::npos){
                        term = cur.substr(pos);
                        pos = cur.length();
                    }
                    else{
                        term = cur.substr(pos, nextPos - pos);
                        pos = nextPos;
                    }
                    int sign = 1;
                    if (term[0] == '-'){
                        sign = -1;
                        term = term.substr(1);
                    }
                    else if (term[0] == '+'){
                        term = term.substr(1);
                    }
                    int coef = 1;
                    int exp = 0;
                    int xPos = term.find('x');
                    if (xPos != string::npos){
                        if (xPos > 0){
                            coef = stoi(term.substr(0, xPos)) * sign;
                        }
                        else coef = sign;
                        int caretPos = term.find('^', xPos);
                        if (caretPos != string::npos){
                            exp = stoi(term.substr(caretPos + 1));
                        }
                        else{
                            exp = 1;
                        }
                    }
                    else{
                        coef = stoi(term) * sign;
                        exp = 0;
                    }
                    p.Insert(coef, exp);
                }
                cout << "已成功添加项!" << endl;
                cout << "目前的多项式为：\n";
                cout << p;
            }  
        }
        else if(s == "Restart"){
            p.clear();
            cout << "已清空当前创建的多项式！\n";
        }
    }while(s != "End");
    return i;
}

ostream& operator<<(ostream& o, const Polynomial& p) {
    PolyNode* curr = p.head->next;
    bool isFirst = true; // 用于判断是否是第一个有效项
    while (curr != nullptr) {
        if (curr->coefficient != 0) {
            if (!isFirst) {
                if (curr->coefficient > 0) {
                    o << "+"; 
                }
            }
            if (curr->exponent != 0) {
                if (curr->coefficient != 1 && curr->coefficient != -1) {
                    o << curr->coefficient;
                } else if (curr->coefficient == -1) {
                    o << "-"; // 处理 -1 的情况
                }
                o << "x";
                if (curr->exponent != 1) {
                    o << "^" << curr->exponent;
                }
            } else {
                o << curr->coefficient; // 输出常数项
            }
            isFirst = false; // 标记为已经输出过第一个项
        }
        curr = curr->next;
    }
    if (isFirst) o << "0"; 
    return o;
}

int Polynomial::calculate(int x) const{
    int result = 0;
    PolyNode* curr = head->next;
    while(curr != nullptr){
        result += curr->coefficient * pow(x, curr->exponent);
        curr = curr->next;
    }
    return result;
}

Polynomial Polynomial::derivative() const{
    Polynomial result;
    PolyNode* curr = head->next;
    while(curr != nullptr){
        if(curr->exponent != 0){
            result.Insert(curr->exponent * curr->coefficient, curr->exponent - 1);
        }
        curr = curr->next;
    }
    return result;
}
