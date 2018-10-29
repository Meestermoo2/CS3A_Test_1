#include "expression.h"

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
{ // Sets all expressions to zero
    clearLibrary();
}

void expression::initializeMap()
{ //Creates a key-value pair
    commandMap["let"] = LET;
    commandMap["print"] = PRINT;
    commandMap["load"] = LOAD;
    commandMap["save"] = SAVE;
    commandMap["eval"] = EVAL;
    commandMap["display"] = DISPLAY;
}

void expression::choice(const std::string &input,
                        const std::string &argument)
{ // Maps a given input to our predefined functions
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

        case DISPLAY:
            display();
            break;

        default:
            exit(1); // replace with throw error?
    }
}

void expression::nthDerivative(const int index, const int source, int n)
{
    while (n > 0){
        library[index] = firstDerivative(library[source]);
        n--;
    }
}

void expression::add(const int index, const int arg1, const int arg2)
{
    library[index] = library[arg1] + library[arg2];
}
void expression::subtract(const int index, const int arg1, const int arg2)
{
    library[index] = library[arg1] - library[arg2];
}
void expression::multiply(const int index, const int arg1, const int arg2)
{
    library[index] = library[arg1] * library[arg2];
}

void expression::load(const std::string &arg)
{ // Loads preconfigured library of expression to current working library
    std::ofstream out;
    std::ifstream in;
    std::string filename = arg;

    // Open with arg name, check to overwrite
    if(filename.find('.') > filename.size())
      filename+= ".exp";
    in.open(filename);
    if((in.fail()))
    {
        std::cout << "The input file does not exist!" << std::endl;
    }
    else
    {
        in >> *this;
        std::cout << "Load successful." << std::endl;
    }


}

void expression::save(std::string arg)
{ // Saves current expression library to file while checking for existing file
    std::ofstream out;
    std::ifstream in;
    std::string filename = arg;

    char ans;
    if(filename.find('.') > filename.size())
        filename += ".exp";
    in.open(filename);
    in.close();
    if(in.fail())
        out.open(filename);
    else
    {
        in.clear();
        std::cout<<"That file exists!!"<< std::endl;
        std::cout<<"Do you wish to overwrite it?" << std::endl;
        std::cin >> ans;
        if(ans == 'Y' || ans == 'y')
            out.open(filename);
        else
        {
            std::cout << "You chose not to overwrite." << std::endl;
//          return;
        }
    }

    out << *this; // Writes to file
    std::cout << "Save successful." << std::endl;
}

void expression::let(const std::string &arg)
{ // Configures an given expression derived from arg to a poly, also derived
  // from arg. E.g. "F=3X^3" etc.
    std::stringstream temp;
    char index; // Holds first char to be used as index
    char junk; // Will hold '='

    temp << arg;
    temp >> index >> junk;
    index = toupper(index);
    term a(0,0);
    polynomial b(a);
    library[index-65] = b; // Sets the destination expression to zero before insertion
    temp >> library[index-65];

    // Displays a successful configuration
    std::cout << std::endl << index << " = "
              << library[int(index-65)] << std::endl;
}
void expression::print(const std::string &arg) {
    // if arg is greater than one char, need to throw error
    std::cout << arg[0] << " = " << library[toupper(arg[0])-65] << std::endl;
}

void expression::clearLibrary()
{ // Clears library by setting all expressions to 0.
    for (unsigned int i = 0; i < 26; ++i)
    {
        term a(0,0);
        polynomial b(a);
        library[i] = b;
    }
}

void expression::display()
{ // Display the current library of expressions
    std::cout << std::endl;
    for(unsigned int i = 0; i < 26; ++i)
    {
        std::cout<< (char)(i+65) << " = " << library[i] <<"\n";
    }
    std::cout << std::endl;
}

void expression::eval(const std::string &arg)
{ // Evaluates a given expression with the value;
    std::stringstream ss;
    fraction temp_frac;
    char index, junk;

    ss << arg;
    ss >> index >> junk;
    index = toupper(index);

    ss >> temp_frac;
    ss >> junk;

    std::cout << std::endl << index // Used for display purposes
              << '(' << temp_frac << ')' << " = "
              << evaluate(temp_frac, library[index-65])
              << std::endl;
}
