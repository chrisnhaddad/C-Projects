//Christopher Haddad - hw08 - Polynomial.h - may 3

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

namespace Poly{
    class Polynomial{

        friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);

        friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
        
        public:
            Polynomial();

            Polynomial(const std::vector<int>& vec);

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
}
#endif