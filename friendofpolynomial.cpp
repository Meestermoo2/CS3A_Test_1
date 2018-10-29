#include "polynomial.h"

polynomial firstDerivative(const polynomial &other)
{
    polynomial temp;
    term newTerm;
    for(unsigned int i = 0; i < other.poly.size(); ++i)
    {
        newTerm.setTerm(
            other[i].getCoeff()*other[i].getPower() ,
            other[i].getPower()-1
            );
        temp.poly.push_back(newTerm);
    }
    temp.sort();
    return temp;
}

std::string nthDerivative(const polynomial &other, int n)
{
    std::stringstream nthderivative;
    polynomial temp = other;

    while (n > 0){
        temp = firstDerivative(temp);
        n--;
    }
    nthderivative << temp;
    return nthderivative.str();
}

polynomial operator+(const polynomial &x, const polynomial &y)
{
    polynomial temp;
    for(unsigned int i = 0; i < x.poly.size(); ++i)
        temp.poly.push_back(x[i]);
    for(unsigned int i = 0; i < y.poly.size(); ++i)
        temp.poly.push_back(y[i]);
    temp.sort();
    temp.combineTerms();
    return temp;
}


polynomial operator-(const polynomial &x, const polynomial &y)
{
    polynomial temp = x + y;
    return temp;
}


polynomial operator*(const polynomial &x, const polynomial &y)
{
    polynomial temp;
    for(unsigned int i = 0; i < x.poly.size(); ++i)
        for(unsigned int j = 0; j < y.poly.size(); ++j)
            temp.poly.push_back(x[i] * y[j]);
    temp.sort();
    temp.combineTerms();
    return temp;
}

fraction evaluate(const fraction &frac, polynomial &y)
{
    fraction temp = 0;
    for(unsigned int i = 0; i < y.poly.size(); ++i)
    {
        temp += y.poly[i].evaluate(frac);
    }
    return temp;
}

std::ostream& operator<<(std::ostream& out, const polynomial &other)
{
    for(unsigned int i = 0; i < other.poly.size(); ++i)
    {
        if (i > 0) // need logic for negative polynomial
        {
            if (other[i].getCoeff() > 0)
                out << "+";
        }

        if (other[i].getCoeff() != 0)
            out<<other[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, polynomial &p)
{
    std::string possiblePoly;
    std::stringstream ss;
    if(&in == &std::cin)
    {
        if(in >> possiblePoly)
        {
            ss << possiblePoly;
            ss >> p;
        }
    }
    else
    {
        term temp;

        while(!in.eof())
        {
            in >> temp;
            p.addTerm(temp);
        }
        in.clear();
        p.sort();
        p.combineTerms();
    }

    return in;

}
