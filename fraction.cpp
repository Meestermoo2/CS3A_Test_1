#include "fraction.h"

fraction::fraction()
{
    num = 0;
    denom = 1;
}
fraction::fraction(int n, int d)
{
   setValue(n,d);
}
fraction::~fraction()
{
    num = denom = 0;
}
fraction::fraction(const fraction &frac)
{
    num = frac.num;
    denom = frac.denom;
}

fraction::fraction(const double &other)
{
    std::string wholePart, fractionPart;
    std::stringstream ss;
    ss<<other;
    getline(ss,wholePart,'.');
    getline(ss,fractionPart);
    if (fractionPart.empty())
            fractionPart = "0";
    int numDigits = fractionPart.size();
    denom = makeDenom(numDigits, allDecimalsTheSame(fractionPart));
    num = denom * std::stoi(wholePart) + std::stoi(fractionPart);
    reduce();
}

bool fraction::allDecimalsTheSame(const std::string &fracPart)
{
    bool yes = true;
    for(int i = 1; yes && i < fracPart.size(); ++i)
        yes = (fracPart[0] == fracPart[i]);
    return yes;
}

int fraction::makeDenom(int digits, bool same)
{
    std::string result("1");
    for(int i = 0; i < digits; ++i)
        result += "0";
    return std::stoi(result) - (int)same * 1;
}

fraction& fraction::operator=(const fraction &frac)
{
    if(this != &frac)
    {
        num = frac.num;
        denom = frac.denom;
    }
    return *this;
}

fraction& fraction::operator+=(const fraction &other)
{
    *this = *this + other;
    return *this;
}

fraction& fraction::operator-=(const fraction &other)
{
    *this = *this - other;
    return *this;
}

fraction& fraction::operator*=(const fraction &other)
{
    *this = *this * other;
    return *this;
}

fraction& fraction::operator/=(const fraction &other)
{
    *this = *this / other;
    return *this;
}


int fraction::getNum()
{
    return num;
}

int fraction::getDenom()
{
    return denom;
}

void fraction::setValue(int n, int d)
{
    num = n;
    denom = d;
    reduce();
}

void fraction::display()
{
    std::cout<<" "<<num;
    if(denom != 1)
       std::cout<<"/"<<denom<<" ";
}


void fraction::getInput()
{
    char junk;
    std::cin>>num>>junk>>denom;
    reduce();
}


void fraction::reduce()
{
    bool neg = num < 0 || denom < 0,
         both = num < 0 && denom < 0;
    int divisor = gcd(abs(num), abs(denom));
    num = abs(num) / divisor;
    denom = abs(denom) / divisor;
    if(!both)
        if(neg)
            num *= -1;
}

int fraction::gcd(int p, int q)
{
   return !q ? p : gcd(q, p%q);
}

