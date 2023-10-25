//Christopher Haddad - hw08 - Polynomial.cpp - may 3
#include "Polynomial.h"
#include <string>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

namespace Poly{
    //the output operator traverses the polynomial. It has many exceptions to deal with
    //such as when the coefficient is 1,-1, or 0 and when the exponent is 1 or 0.
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

    //The == operator first checks if the degree of both polynomials is equal because
    //if not, then they are automatically not equal. If they are it goes through 
    //polynomials comparing each node's data. If there is a node where the data
    //is not equal then it returns false. if they are all equal it returns true.
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

    //the default constructor sets head to a default node and sets the degree of the
    //polynomial to 0.
    Polynomial::Polynomial(){
        head = new Node();
        degree = 0;
    }

    //the constructor takes in a vector. it first sets the first item in
    //the vector as the head. it then traverses the vector making a new node
    //for each item creating a singly linked list. the cleanup method is then called.
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

    //the cleanup method goes through the list while the head node's data is 0
    //and the next node is not nullptr to not accidentally remove the 0 degree value if
    //it is equal to 0.
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

    //the += operator first checks if rhs.degree is larger. If it is the difference is found
    //and that number of nodes is added to the front of this polynomial. it checks the difference
    //again for the case when this has a greater degree than rhs. it goes up p the amount of 
    //times as difference to get to the same degree as rhs. It then just goes through rhs and 
    //p adding rhs's data from each node to p's data at the same degrees.
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

    //the copy constructor goes through rhs and makes a new node for each node of rhs.
    Polynomial::Polynomial(const Polynomial& rhs){
        degree = rhs.degree;
        head = new Node{rhs.head->data};
        Node* cursor = head;
        for (Node* p = rhs.head->next; p!=nullptr; p = p->next){
            cursor->next = new Node{p->data};
            cursor = cursor->next;
        }
    }

    //the destructor goes through the polynomial removing one node at a time by 
    //creating a temp, setting p to p->next, and then deleting temp.
    Polynomial::~Polynomial(){
        Node* p = head;
        while (p!= nullptr){
            Node* temp = p;
            p = p->next;
            delete temp;
        }
        head = nullptr;
    }

    //the assignment operator first checks if this is not equal to the adress of 
    //rhs. it then uses the same code from the destructor followed by the same code from the 
    //copy constructor.
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

    //the evaluate method uses horner's method.
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

    //the + operator makes a copy of lhs by setting it to result. it then uses the += operator on result 
    //by adding rhs. it then returns this result.
    Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
        Polynomial result = lhs;
        result+=rhs;
        return result;
    }

    //the != operator just returns the opposite as the == operator.
    bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
        return !(lhs==rhs);
    }

    //do nothing
    void doNothing(Polynomial temp) {}
}