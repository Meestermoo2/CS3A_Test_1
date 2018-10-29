#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "polynomial.h"
#include <map>

class expression
{

    enum commands { ERROR, LET, EVAL, PRINT, LOAD, SAVE, DISPLAY };

    std::map<std::string, expression::commands> commandMap;
    void initializeMap();

public:
    expression();
    ~expression();
    void choice(const std::string &input, const std::string &argument=""); // this should access the private functions
    void clearLibrary();
    void nthDerivative(const int index, const int source, int n);
    void add(const int index, const int arg1, const int arg2);
    void subtract(const int index, const int arg1, const int arg2);
    void multiply(const int index, const int arg1, const int arg2);
//    void divide(const int index, const int source);


    friend
    std::ostream& operator<<(std::ostream& out, const expression &other);
    friend
    std::istream& operator>>(std::istream& in, expression &e);

private:
    polynomial library[26];
    void let(const std::string &arg);
    void eval(const std::string &arg);
    void print(const std::string &arg);
    void load(const std::string &arg);
    void save(const std::string arg);
    void display();

};


#endif // EXPRESSION_H
