#include <iostream>
using namespace std;

typedef struct PolyNode{
    int coef;
    int exp;
    struct PolyNode* next;

    PolyNode(int c = 0, int e = 0 , struct PolyNode* n = nullptr):coef(c),exp(e),next(n){}
}PolyNode;

class Polynomial{
    private:
        PolyNode* head;
    public:
        Polynomial();
        Polynomial(PolyNode* h);
        Polynomial(const Polynomial& other);
        ~Polynomial();
        Polynomial operator+(Polynomial& other);
        Polynomial operator-(Polynomial& other);
        int calculate(int x);         
        Polynomial derivative();    
        Polynomial operator*(Polynomial& other);    
        friend ostream& operator<<(ostream& o, Polynomial& p);           
        friend istream& operator>>(istream& i, Polynomial& p);
};