#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) { }

BitcoinExchange::BitcoinExchange(const char *path)
{
    std::ifstream   file;
    std::string     line;
    std::string     date;
    size_t          pos;
    float           value;

    file.open(path);
    if (!file.is_open())
        throw FailOpenException();
    while (getline(file, line))
    {
        pos = line.find(',');
        date = line.substr(0, pos);
        value = strtof(line.substr(pos +1).c_str(), NULL);
        _exchangeRate[date] = value;
    }
    file.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
    *this = src;
}

BitcoinExchange::~BitcoinExchange(void) { }

BitcoinExchange    &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
    if (this != &rhs)
        this->_exchangeRate = rhs._exchangeRate;
    return (*this);
}

void        BitcoinExchange::printLine(const std::string &date, const float &amount)
{
    if (!checkDate(date))
    {
        std::cout << "Error: " << date << " is not a valid date" << std::endl;
        return;
    }
    else if (!checkAmount(amount))
        return;
    else
    {
        std::cout << date << "-> " << amount << " = " << getFinalValue(date, amount) << std::endl;
    }
}

bool    BitcoinExchange::checkDate(const std::string &date)
{
    int     year;
    int     month;
    int     day;
    char    sep;
    std::stringstream sString(date);

    sString >> year >> sep >> month >> sep >> day;
    if (year < 0 || (month < 1  || month > 12) || (day < 1 || day > 31))
        return (false);
    if (month == 4 || month == 6 || month == 8 || month == 10 || month == 12)
    {
        if (day > 30)
            return (false);
    }
    if (month == 2)
    {
        if ((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0))
        {
            if (day > 29)
                return (false);
        }
        else
        {
            if (day > 28)
                return (false);
        }
    }
    return (true);
}

bool    BitcoinExchange::checkAmount(const float &amount)
{
    if (amount < 0)
    {
        std::cerr << "Error: " << amount << " isn't a positive number." << std::endl;
        return (false);
    }
    if (amount > 1000)
    {
        std::cerr << "Error: " << amount << " is a too large number." << std::endl;
        return (false);
    }
    return (true);
}

float   BitcoinExchange::getFinalValue(const std::string &date, const float &amount) const
{
    std::map<std::string, float>::const_iterator    it;

    it = _exchangeRate.find(date);
    if (it == _exchangeRate.end())
    {
        it = _exchangeRate.lower_bound(date);
        if (it == _exchangeRate.end())
        {
            std::cout << "Error during key searching" << std::endl;
            return (-1);
        }
        it--;
    }
    return (amount * it->second);
}

const char *BitcoinExchange::FailOpenException::what() const throw()
{
    return ("Error : Cannot open data.csv file");
}

const char *BitcoinExchange::EmptyFileException::what() const throw()
{
    return ("Error : Input file is empty");
}