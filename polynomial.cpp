#include "polynomial.h"

polynomial::polynomial()
{ // Creates a polynomial with 0X^0
    term a;
    poly.push_back(a);
}

polynomial::~polynomial()
{
    poly.clear();
}

polynomial::polynomial(const polynomial &other)
{
    copy(other);
}

polynomial::polynomial(const term &other)
{
    poly.push_back(other);
}

polynomial& polynomial::operator=(const polynomial &other)
{
    if(this != &other)
    {
        poly.clear();
        copy(other);
    }
    return *this;
}

polynomial& polynomial::operator+=(const polynomial &other)
{
    polynomial ans = *this + other;
    *this = ans;
    return *this;
}

polynomial& polynomial::operator-=(const polynomial &other)
{
    polynomial ans = *this - other;
    *this = ans;
    return *this;

}

polynomial& polynomial::operator*=(const polynomial &other)
{
        polynomial ans = *this * other;
        *this = ans;
        return *this;
}


fraction polynomial::operator()(const fraction &other)
{
    fraction result;
    for(unsigned int i = 0; i < poly.size(); ++i)
        result += poly[i](other);
    return result;
}


term polynomial::operator[](unsigned int index) const
{
    return poly[index];
}

term& polynomial::operator[](unsigned int index)
{
    return poly[index];
}

void polynomial::copy(const polynomial &other)
{
    for(unsigned int i = 0; i < other.poly.size(); ++i)
        poly.push_back(other[i]);
}

void polynomial::sort()
{
    term temp;
    for(unsigned int i = 0; i < poly.size(); ++i)
        for(unsigned int j = 0; j < poly.size(); ++j)
            if(poly[i] > poly[j])
            {
                temp = poly[i];
                poly[i] = poly[j];
                poly[j] = temp;
            }
}

void polynomial::combineTerms()
{
    for(std::vector<term>::iterator it = poly.begin(); it != poly.end()-1; ++it)
    {
        if(it->getPower() == (it+1)->getPower())
        {
            it->setTerm(it->getCoeff() + (it+1)->getCoeff(),
                            (it+1)->getPower());
            poly.erase(it+1);
        }
    }
}

void polynomial::addTerm(const term &t) {
    term temp = t;
    bool matchFound = false;
    for (unsigned int i = 0; i < poly.size(); ++i)
    {
        if (temp.getPower() == poly[i].getPower())
        {
            poly[i]+=temp;
            matchFound = true;
        }
    }

    if (!matchFound)
        poly.push_back(temp);
}
