#include "expression.h"
#include <string>

std::ostream& operator<<(std::ostream& out, const expression &e)
{
    for(unsigned int i = 0; i < 26; ++i)
    {
        out<< char(i+65) << "=" << e.library[i] <<"\n";
    }
    return out;
}

std::istream& operator>>(std::istream& in, expression &e)
{
    std::string line, possiblyPoly;
    std::stringstream ss, ss_poly;
    polynomial poly_temp;
    char junk;
    char index;

    e.clearLibrary();
    for(unsigned int i = 0; i < 26; ++i)
    {
        getline(in, line);
//        std::cout<<line<<std::endl;
        ss << line;

        ss >> index;
        index = toupper(index);
//        std::cout << index << std::endl;
        ss >> junk;
//        std::cout << junk << std::endl;
        ss >> e.library[int(index-65)]; //
//        std::cout << temp << std::endl;

//        e.library[int(index-65)] = poly_temp;

//        std::stringstream asdf;
//        asdf << random;
//        asdf >> e.library[13];

        ss.clear();

    }


    return in;
}
