#include <iostream>
#include "BitcoinExchange.hpp"

void    getValue(std::ifstream &input)
{
    BitcoinExchange rate("data.csv");
    std::string line;
    std::string date;
    float       amount;
    size_t      pos;

    if (input.peek() == std::ifstream::traits_type::eof())
        throw BitcoinExchange::EmptyFileException();
    getline(input, line);
    while (getline(input, line))
    {
        pos = line.find('|');
        if (pos == std::string::npos)
        {
            std::cerr << "Error : Bad input => " << line <<std::endl;
        }
        else
        {
            date = line.substr(0,pos);
            amount = strtof(line.substr(pos +1).c_str(), NULL);
            rate.printLine(date, amount);
        }
    }
}

int main(int argc, char **argv)
{
    std::ifstream input;

    if (argc != 2)
    {
        std::cerr << "Error : Wrong number of arguments" << std::endl;
        return (1);
    }
    input.open(argv[1]);
    if (!input.is_open())
    {
        std::cerr << "Error: Cannot open \"" << argv[1] << "\" file" << std::endl;
        return (2);
    }
    try
    {
        getValue(input);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    input.close();

    return (0);
}