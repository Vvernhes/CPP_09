#include <iostream>
#include "RPN.hpp"

void    parseArg(const char *argv)
{
    unsigned int index;
    RPN         myRPN;

    index = 0;
    if (argv[index] == '\0')
        throw RPN::EmptyArgumentGiven();
    while (argv[index])
    {
        if (argv[index] >= '0' && argv[index] <= '9')
        {
            if (!argv[index + 1] || argv[index + 1] != ' ')
            {
                std::cerr << "Error: wrong format of argument" << std::endl;
                return;
            }
            myRPN.addNumber(argv[index] - '0');
        }
        else if (argv[index] == '+' || argv[index] == '-' || argv[index] == '*' || argv[index] == '/')
            myRPN.doCalculation(argv[index]);
        else if (argv[index] != ' ')
        {
            std::cerr << "Error: Wrong format of argument." << std::endl;
            return;
        }
        index++;
    }
    std::cout << myRPN.getResult() << std::endl;
}

int main(int argc, char **argv)
{
    if (argc > 2 || argc == 1)
    {
        std::cerr << "Error: Wrong number of argumets." << std::endl;
        return (1);
    }
    try
    {
        parseArg(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error : " << e.what() << std::endl;
    }
}