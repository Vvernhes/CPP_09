#include "RPN.hpp"

RPN::RPN(void) { }

RPN::RPN(const RPN& src)
{
    *this = src;
}

RPN::~RPN(void) { }

RPN    &RPN::operator=(const RPN &rhs)
{
    if (this != &rhs)
    {
        this->_stackRPN = rhs._stackRPN;
    }
    return (*this);
}

void    RPN::addNumber(const int &nb)
{
    _stackRPN.push(nb);
}

void    RPN::doCalculation(const char symbol)
{
    int tmp;

    if (_stackRPN.size() < 2)
        throw NotEnoughtNumberException();
    tmp = _stackRPN.top();
    _stackRPN.pop();
    if (symbol == '+')
        _stackRPN.top() = _stackRPN.top() + tmp;
    else if (symbol == '-')
        _stackRPN.top() =  _stackRPN.top() - tmp;
    else if (symbol == '*')
        _stackRPN.top() = _stackRPN.top() * tmp;
    else if (symbol == '/')
    {
        if (tmp == 0)
            throw DivisionByZeroException();
        _stackRPN.top() = _stackRPN.top() / tmp;
    }
    else
       throw BadSymbolException();
}

int     RPN::getResult(void) const
{
    if (_stackRPN.size() != 1)
        throw TooMuchNumberException();
    return (_stackRPN.top());
}

const char* RPN::NotEnoughtNumberException::what() const throw()
{
    return ("Not enought numbers in RPN");
}

const char* RPN::BadSymbolException::what() const throw()
{
    return ("Bad symbol given");
}

const char* RPN::TooMuchNumberException::what() const throw()
{
    return ("Too much numbers in RPN");
}

const char* RPN::EmptyArgumentGiven::what() const throw()
{
    return ("Empty argument given");
}

const char* RPN::DivisionByZeroException::what() const throw()
{
    return ("Division by 0 impossible");
}