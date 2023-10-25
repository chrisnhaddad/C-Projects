#include <string>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;


class Polynomial{

    friend ostream& operator<<(ostream& os, const Polynomial& rhs);

    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    
    public:
        Polynomial();

        Polynomial(const vector<int>& vec);

        void cleanup();

        Polynomial& operator+=(const Polynomial& rhs);

        Polynomial(const Polynomial& rhs);

        ~Polynomial();

        Polynomial& operator=(const Polynomial& rhs);

        int evaluate(int num) const;

    private:
        struct Node{
            int data = 0;
            Node* next = nullptr;
        };

        Node* head;
        int degree;

};

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

bool operator!=(const Polynomial& lhs, const Polynomial& rhs);

void doNothing(Polynomial temp);

int main() {
        
    //test constructor
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7

    // Polynomial temp(p4);
    // cout << "temp: " << temp << endl;
        
    //    cerr << "displaying polynomials\n";
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "has_a_zero: " << has_a_zero << endl;

    // Polynomial temp;
    // temp = p2 + p3;
    // cout << "temp: " << temp << endl;
    
    cout << "p2 + p3: " << (p2+p3) << endl; 
    cout << "p2 + p4: " << (p2+p4) << endl; 
    cout << "p4 + p2: " << (p4+p2) << endl;

    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;  
    cout << "p5: " << p5 << endl;  


    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;


    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
        
    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

    Polynomial p8({ 1, 1 });
    Polynomial p9({ -1, 1 });
    Polynomial p10({ 0, 0, 2 });
    //p8 + p9 tests if += does the cleanup()
    //p10 tests if constructor does the cleanup()

    cout << "p8: " << p8 << endl
         << "p9: " << p9 << endl
         << "p10: " << p10 << endl;

    cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;
}


ostream& operator<<(ostream& os, const Polynomial& rhs){
    Polynomial::Node* pos = rhs.head;
    int deg = rhs.degree;
    for (Polynomial::Node* pos = rhs.head; pos!=nullptr; pos = pos->next){
        if (pos->data != 0){
            if (pos != rhs.head){
                os<<'+';
            }
            if (deg == 0){
                os<< pos->data;
                break;
            }
            if (pos->data == 1){
                os<< "x";
            } else if (pos->data == -1){
                os<<"-x";
            }else{
                os<< pos->data << "x";
            }
            if (deg!= 0 && deg!=1){
                os<<'^'<<deg;
            }
        }
        if (pos->data==0 && deg==0){
            os<<"0";
        }
        deg-=1;
    }
    return os;
}


bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial::Node* lhscopy = lhs.head;
    Polynomial::Node* rhscopy = rhs.head;
    if (rhs.degree == lhs.degree){
        while (lhscopy != nullptr){
            if (lhscopy->data != rhscopy->data){
                return false;
            }
            lhscopy = lhscopy->next;
            rhscopy = rhscopy->next;
        }
    } else{
        return false;
    }
    return true;
}


Polynomial::Polynomial(){
    head = new Node();
    degree = 0;
}

Polynomial::Polynomial(const vector<int>& vec){
    head = new Node{vec[0]};
    Node* pos = head;
    for (size_t i = 1; i<vec.size(); ++i){
        pos->next = new Node{vec[i]};
        pos = pos->next;
    }
    degree = vec.size()-1;
    this->cleanup();
}

void Polynomial::cleanup(){
    Node* p = head;
    while (p->next!=nullptr && p->data == 0){
        Node* temp = p;
        p = p->next;
        delete temp;
        temp = nullptr;
        degree--;
    }
    head = p;
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs){
    if (rhs.degree>degree){
        int diff = rhs.degree - degree;
        for (size_t i = 0; i<diff; ++i){
                head = new Node{0, head};
        }
        degree = rhs.degree;
    }
    Node* p = head;
    Node* rhscopy = rhs.head;
    int diff = degree - rhs.degree;
    for (size_t i = 0; i<diff; ++i){
        p = p->next;
    }
    while (rhscopy!=nullptr){
        p->data+=rhscopy->data;
        rhscopy = rhscopy->next;
        p = p->next;

    }
    this->cleanup();
    return *this;
}

Polynomial::Polynomial(const Polynomial& rhs){
    degree = rhs.degree;
    head = new Node{rhs.head->data};
    Node* cursor = head;
    for (Node* p = rhs.head->next; p!=nullptr; p = p->next){
        cursor->next = new Node{p->data};
        cursor = cursor->next;
    }
}

Polynomial::~Polynomial(){
    Node* p = head;
    while (p!= nullptr){
        Node* temp = p;
        p = p->next;
        delete temp;
    }
    head = nullptr;
}

Polynomial& Polynomial::operator=(const Polynomial& rhs){
    if (this!=&rhs){
        Node* p = head;
        while (p!= nullptr){
            Node* temp = p;
            p = p->next;
            delete temp;
        }
        head = nullptr;
        degree = rhs.degree;
        head = new Node{rhs.head->data};
        Node* cursor = head;
        for (Node* p = rhs.head->next; p!=nullptr; p = p->next){
            cursor->next = new Node{p->data};
            cursor = cursor->next;
        }
    }
    return *this;
}

int Polynomial::evaluate(int num) const{
    int result;
    Node* p = head;
    result = p->data;
    for (size_t i = 0; i<degree; ++i){
        p=p->next;
        result = result*num + p->data;
    }
    return result;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial result = lhs;
    result+=rhs;
    return result;
}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs==rhs);
}

void doNothing(Polynomial temp) {}