#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <exception>

class BitcoinExchange
{
    public:
        BitcoinExchange(const char *path);
        BitcoinExchange(const BitcoinExchange& src);
        ~BitcoinExchange(void);
        BitcoinExchange& operator=(const BitcoinExchange& rhs);
        void    printLine(const std::string &date, const float &amount);

        class FailOpenException : public std::exception
        {
            virtual const char* what() const throw();
        };

        class EmptyFileException :public std::exception
        {
            virtual const char* what() const throw();
        };

    private:
        std::map<std::string, float>    _exchangeRate;

        bool    checkDate(const std::string &date);
        bool    checkAmount(const float &amount);
        float   getFinalValue(const std::string &date, const float &amount) const;
        BitcoinExchange(void);
};

#endif