#include "expression.h"
#include "string.h"

expression::expression()
{ // constructor definition
    for (unsigned int i = 0; i < 26; ++i)
    {
        term a(0,0);
        polynomial b(a);
        library[i] = b;
    }
    initializeMap();
}

expression::~expression()
{
    clearLibrary();
}

polynomial expression::getFunction(int index)
{
    std::cout << library[index];
}

void expression::setFunction(int index)
{ // set function
    term temp(0,0);
    polynomial a(temp);
    std::cin >> a;
    library[index] = a;
}

void expression::choice(const std::string &input,
                        const std::string &argument)
{
    std:: string temp_str;

    for (unsigned int i = 0; i < input.length(); ++i)
    {
        temp_str += tolower(input[i]);
    }

    switch(commandMap[temp_str])
    {
        case LET:
            let(argument);
            break;

        case EVAL:
            eval(argument);
            break;

        case PRINT:
            print(argument);
            break;

        case LOAD:
            load(argument);
            break;

        case SAVE:
            save(argument);
            break;

//        case DISPLAY:
//            display();
//            break;

        default:
            exit(1); // replace with throw error
    }
}

void expression::load(std::string arg)
{
    using namespace std;
    ofstream out;
    ifstream in;

    char ans;
    //open with arg name, check to overwrite
    if(arg.find('.') > arg.size())
      arg += ".exp";
    in.open(arg);
    if((in.fail()))
    {
        cout << "The input file does not exist" << endl;
        exit(1);
    }

    in >> *this;
    std::cout << "Load succesful." << std::endl;
}

void expression::save(std::string arg){
    using namespace std;
    ofstream out;
    ifstream in;

    char ans;
    //open with arg name, check to overwrite
    if(arg.find('.') > arg.size())
      arg += ".exp";
    in.open(arg);
    in.close();
    if(in.fail())
     out.open(arg);
    else
    {
      in.clear();
      cout<<"That file exists!!"<<endl;
      cout<<"Do you wish to overwrite it" << endl;
      cin >> ans;
      if(ans == 'Y' || ans == 'y')
          out.open(arg);
      else
      {
          cout << "You chose not to overwrite" << endl;
          return;
      }
    }

    //write to file
    out << *this;
    std::cout << "Save succesful." <<std::endl;
}

void expression::initializeMap()
{
    commandMap["let"] = LET;
    commandMap["print"] = PRINT;
    commandMap["load"] = LOAD;
    commandMap["save"] = SAVE;
    commandMap["eval"] = EVAL;
    commandMap["display"] = DISPLAY;
    // add display
}

void expression::let(const std::string &arg)
{
    std::stringstream temp;
    temp << arg;
    char index;
    char junk;
    temp >> index >> junk;
    index = toupper(index);
    term a(0,0);
    polynomial b(a);
    library[int(index-65)] = b;
    temp >> library[int(index-65)];

}
void expression::print(const std::string &arg) {
    // if arg is greater than one char, need to throw error
    std::cout << arg[0] << " = " << library[toupper(arg[0])-65] << std::endl;
}

//    //open object with arg name
//
//    ostream output;
//
//    std::ostream << library[2];

void expression::clearLibrary()
{
    for (unsigned int i = 0; i < 26; ++i)
    {
        term a(0,0);
        polynomial b(a);
        library[i] = b;
    }
}

//void expression::display()
//{
//    for(unsigned int i = 0; i < 26; ++i)
//    {
//        std::cout<< char(i+65) << "=" << library[i] <<"\n";
//    }
//}

void expression::eval(const std::string &arg)
{
    std::stringstream ss;
    fraction temp_frac;
    char index, junk;

    ss << arg;
    ss >> index >> junk;
    index = toupper(index);

    ss >> temp_frac;
    ss >> junk;

    std::cout << index << '(' << temp_frac << ')'
              << '=' << evaluate(temp_frac, library[int(index-65)])
              << std::endl;

}
