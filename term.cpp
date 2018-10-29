#include "term.h"

term::term(char v)
{
    coeff = power = 0;
    variable = v;
}

term::term(const fraction &c, const fraction& p)
{
    power = p;
    coeff = c;
}

term::~term()
{
    coeff = power = 0;
    variable = ' ';
}

term::term(const term& other)
{
    copy(other);
}

term& term::operator=(const term& other)
{
    if(this != &other)
        copy(other);
    return *this;
}


fraction term::getPower()
{
    return power;
}

fraction term::getCoeff()
{
    return coeff;
}

void term::setTerm(const fraction &c, const fraction p)
{
    power = p;
    coeff = c;
}


term& term::operator*=(const term& other)
{
    return (*this = *this * other);
}

term& term::operator/=(const term& other)
{
    return (*this = *this / other);
}

term& term::operator+=(const term& other)
{
    term temp = *this + other;
    if(temp != 0)
        *this = temp;
    return *this;
}

term& term::operator-=(const term& other)
{
    term temp = *this - other;
    if(temp != 0)
        *this = temp;
    return *this;
}

fraction term::evaluate(const fraction& other)
{
   return ((this->coeff)*(other^(this->power)));
}

fraction term::operator()(const  fraction& other)
{
   return evaluate(other);
}


void term::copy(const term &other)
{
    coeff = other.coeff;
    power = other.power;
}
