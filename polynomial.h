#ifndef polynomial_H
#define polynomial_H
#include <iostream>
#include <fstream>
#include <vector>
#include "term.h"
#include "fraction.h"

class polynomial
{
    public:
        polynomial();
        ~polynomial();
        polynomial(const term &other);
        polynomial(const polynomial &other);
        void addTerm(const term &t);
        polynomial& operator=(const polynomial &other);
        polynomial& operator+=(const polynomial &other);
        polynomial& operator-=(const polynomial &other);
        polynomial& operator/=(const polynomial &other);
        polynomial& operator*=(const polynomial &other);
        fraction operator()(const fraction &other);
        term operator[](unsigned int index) const;
        term& operator[](unsigned int index);

        friend
        polynomial firstDerivative(const polynomial &other);

        friend
        fraction evaluate(const fraction &frac, polynomial &y);

        friend
        polynomial operator+(const polynomial &x, const polynomial &y);

        friend
        polynomial operator-(const polynomial &x, const polynomial &y);

        friend
        polynomial operator*(const polynomial &x, const polynomial &y);

        friend
        std::ostream& operator<<(std::ostream& out, const polynomial &p);

        friend
        std::istream& operator>>(std::istream& in,  polynomial &p);

        friend
        std::string nthDerivative(const polynomial &other, int n);



private:
        std::vector<term> poly;

        void copy(const polynomial &other);
        void sort();
        void combineTerms();
};

#endif // polynomial_H
