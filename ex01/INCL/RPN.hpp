#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <iostream>
#include <string>
#include <exception>

class RPN
{
    public:
        RPN(void);
        RPN(const RPN& src);
        ~RPN(void);
        RPN& operator=(const RPN& rhs);
        void    addNumber(const int &nb);
        void    doCalculation(const char symbol);
        int     getResult(void) const;

        class NotEnoughtNumberException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

        class BadSymbolException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

        class TooMuchNumberException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

        class EmptyArgumentGiven : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

        class DivisionByZeroException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

    private:
        std::stack<int>     _stackRPN;
};

#endif