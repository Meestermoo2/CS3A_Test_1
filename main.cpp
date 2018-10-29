/* Algebraic polynomial Calculator
The goal of this project is for you to develop a "command line" Algebraic polynomial calculator that will accept up to 26 arbitrarily long algebraic polynomials composed of terms, as described above.

Goal #1. The program, named calculate, if started on the command line with no parameters, when ready for input, a prompt such as INPUT: or COMMAND: must be printed.
After each successful operation, this prompt will re-appear asking for the next command. Naturally, if the user enters just the return key, then the program will terminate.

Goal #2. They can enter one of the following commands: LET, EVAL, or PRINT.
a. The command LET must be followed by a space, then a letter (A – Z), a space, then an equal sign (=), then by the algebraic polynomial the user wishes to assign to this letter. (e.g. LET F = 2X + 4.
The result printed upon successful completion will be F = 2X + 4 in this example.

b. The command EVAL must be followed by a space, then the letter representing a pre-stored algebraic polynomial, followed by the value within parentheses. (e.g. EVAL F(1/4) ) The program will then print F(1/4) = 4 1/2

c. The command PRINT must be followed by a space then the letter representing a pre-stored algebraic polynomial (e.g PRINT F). The program will respond by printing F = 2X + 4, for example.
Goal #3.
2. They can enter one of the following:

a. An polynomial, such as F = G + H, where F, G, and H are all pre-stored algebraic polynomials. Upon completion, the program will print F = 2X + 4, for example.

b. An polynomial, such as F = G - H, where F, G, and H are all pre-stored algebraic polynomials. Upon completion, the program will print F = 2X + 4, for example.

c. An polynomial, such as F = G * H, where F, G, and H are all pre-stored algebraic polynomials. Upon completion, the program will print F = 2X + 4, for example

d. An polynomial, such as F = G’, where G’ is the derivative of G. As with the proceeding, the resultant algebraic polynomial will be printed.

e. This is the same as the above, but with the ability to enter an arbitrary derivative (such as F = G’’’). As with the proceeding, the resultant algebraic polynomial will be printed.

3. They can enter LOAD followed by a file name. This will load up to 26 pre-defined, or saved earlier, algebraic polynomials. (See below for additional when there are more than one parameter on the command line)

4. They can enter SAVE followed by a file name. This will save the contents of the 26 algebraic polynomials to a file.
As with all of the programs that you have done, the program must ensure that files are not accidentally overwritten and so forth. File names for these files must end in “.exp”

RULES FOR COMMAND LINE PARAMETERS
When there is one parameter on the command line after the name of the program, it will load the file associated with that name.
If there is no extension on the name given, the default extension of “.exp” must be added to the file name before opening the file. Conversely, if there is a /h or /? As the parameter, then a “help message” must be displayed to the user and the program terminates.


When there are two parameters on the command line after the name of the program, the first parameter must be the word EXECUTE or RECORD.
The next parameter is a “script” file, which is composed of commands, as stated from the above section which deals with input from the command line.
If the word EXECUTE is present, then the program must read the file and perform all of the statements within the file.
If the word in RECORD, then the program must save to a file all of the commands that the user enters in via the command line.
Script files must have an extension of “.spt”; and, as above, the “.spt” must be added if the user did not provide it.


If there are more than two parameters on the command line, then the program must “error out.” This means to notify the user that the program will be quitting and why it did so.

PROGRAM REQUIREMENTS
All values must be stored in a class called Fraction. This class must be able to handle all operations between decimals, fractions, and integers.

All data must be stored as a Fraction with all output given as a Fraction.

Only ONE input stream function in the main.cpp can be written for reading of input (whether it comes from a command line or a file).
Thus, the input function must be passed a parameter telling it which stream is to be used for the reading of commands.
If the commands are coming from a file, they must be echoed to the screen. If the user is entering them, they must not be echoed.

All strings used must be C++ strings.

Exceptions must be used accordingly. Such as when a file does not exist, divide by zero, invalid input, and so forth.

There must be a class called polynomial that will store the polynomials entered. This class must have Fractions for each term of the polynomial. (Hint: dynamic arrays or vectors)

Terms of the polynomial must be stored in either a structure or a class (preferred).
 * */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "fraction.h"
#include "term.h"
#include "polynomial.h"
#include "expression.h"

using namespace std;

void introduction();
bool checkCL(int count);
void getInput(istream& in, expression&a, char *commands[], int count);


void let();
void Eval();
void print();
void getFrac(string title, fraction &frac);
void output(fraction x, fraction y, char op);
void getTerm(string title, term &t);
void getPoly(string title, polynomial &p);
void evaluatePoly(string title, polynomial&p);
void evaluateNthDeriv(string title, polynomial&p);
bool question(string title);
void introduction();

int main(int argc, char *argv[])
{
//    introduction();
//    bool CL = checkCL(argc);
//    do
//    {
//        expression a;
//        ifstream in;

//        if(CL)
//        {
//            //if parameters in command line, we're reading from a file
//            getInput(in, a, argv, argc);
//        }
//        else
//            //read from terminal
//            getInput(cin, a, argv, argc);

//    }while(question("Do you want to do this again? "));



    expression a;

    while(1)
    {
        cout << "input command: \n";
        string temp, arg;
        cin >> temp;
        cin >> arg;
        a.choice(temp, arg);
        std::cout << a << std::endl;
    }

//   while (1)
//   {
//       polynomial a;
//       cin >> a;
//       cout << "\nThis is your polynomial: " << a << std::endl;
//   }

    return 0;
}

void introduction()
{
    string border(80, '*');

    cout << border << endl;
    cout << "This Program is called Calculate and it is an polynomial Calculator that that will accept up to 26 algebraic polynomials." << endl;
    cout << border << endl;
}

bool checkCL(int count)
{
    //if command line containes 1 or 2 parameters (excluding the name of the program)
    if(count == 2 || count == 3)
    {
        return true;
    }
    //if command line contains more than 2 parameters
    else if(count > 3)
    {
        cout << "Error, there are more than 2 parameters on the command line \n"
             << "The program will now exit \n";
        exit(1);
    }
    return false;
}

void getInput(istream& in, expression& a, char *commands[], int count) //expression will be in here as well
{
    ifstream file;
    stringstream ss;
    string line, filename, EXorRE;
    polynomial input;

    //read from terminal, no parameters in command line
    if(&in == &cin)
    {
        cout << "COMMAND: ";

        //choice will go in here

        //IT SEEMS WE WILL NEED SOME CONSTRUCT TO STORE AND MODIFY 26 POLYNOMIALS

        //LET will initialize or change a polynomial variable to some polynomial given by the user (F=2X+4)
        //EVAL will evaluate an already stored polynomial to some value (F(4)=12_
        //PRINT will display an already stored polynomial (F=2X+4)

        //THE USER MAY ALSO TYPE IN EXPRESSIONs LIKE F=G+H, F=G*H, F=G-H, F=G' or F=G''', this will evaluate and print.

        //LOAD followed by a file name will load up a construct of 26 polynomials
        //save will save all 26 polynomials into a file, including any changes made in the program.

    }
    else
    {
        //one parameter after the name of the program
        if(count == 2)
        {
            cout << "There is one parameter in the command line" << endl;

            //load file associated with this parameter
            filename = commands[1];

            if(filename == "/h" || filename == "/?")
            {
                cout << "It seems that you need help, you must include the name of the file that you wish to load" << endl;
                exit(1);
            }

            a.choice("save", filename);


        }
        else if(count == 3)
        {
            cout <<"There are two parameters in the command line" << endl;

            //first argument is a command, either execute or record
            EXorRE = commands[1];

            //this is the name of a script file, which is composed of commands
            filename = commands[2];

            //add .spt to file name if not found
            if(filename.find('.') > filename.size())
                filename += ".spt";
            file.open(filename);
            if((in.fail()))
            {
                cout << "The input file does not exist" << endl;
                exit(1);
            }
        }
    }
}

//void command(string title, istream& in)
//{
//    string line;
//    getline(in, line)
//}

//void getPoly(string title, polynomial &p)
//{
//    cout<<title;
//    cin>>p;
//}

//void getFrac(string title, fraction &frac)
//{
//    cout<<title;
//    cin>>frac;
//}

//void evaluatePoly(string title, polynomial &p)
//{
//    cout << title;
//    fraction input;
//    getFrac("",input);
//    fraction temp;
//    temp = evaluate(input, p);
//    cout << "The final value is: "<< temp;
//    cout << endl;

//}

//void evaluateNthDeriv(string title, polynomial&p)
//{
//    cout << title;
//    int num;
//    cin >> num;
//    cout << nthDerivative(p,num) << endl;
//}
void newLine()
{
    char symbol;
    do
    {
        cin.get(symbol);
    } while (symbol != '\n');
}

bool question(string title)
{
    string border(50, '*');
    string line;
    cout<<title;
    cin >> line;
    newLine();
    cout << border << endl;
    return toupper(line[0]) == 'Y';
}

/* Sample Program

*/
