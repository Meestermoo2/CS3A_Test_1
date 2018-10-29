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
        void setFunction(int index);
        polynomial getFunction(int index);
        friend
        std::ostream& operator<<(std::ostream& out, const expression &other);
        friend
        std::istream& operator>>(std::istream& in, expression &e);
        void clearLibrary();

    private:
        polynomial library[26];
        void let(const std::string &arg);
        void eval(const std::string &arg);
        void print(const std::string &arg);
        void load(const std::string arg);
        void save(const std::string arg);
//        void display();

};


#endif // EXPRESSION_H
