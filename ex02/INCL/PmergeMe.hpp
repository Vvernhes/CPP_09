#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <exception>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <climits>

class PmergeMe
{
    public:
        PmergeMe(void);
        PmergeMe(const PmergeMe& src);
        ~PmergeMe(void);
        PmergeMe& operator=(const PmergeMe& rhs);
        void    start(char **argv, int argc);

        template<typename T>
        void    displayContainer(const T &container);
        template<typename T>
        void    check_arg(T &container, const char *arg);
        void    setKValue(void);
        int     getKValue(void) const;
        void    launchList(void);
        void    launchDeque(void);
        void    checkDuplicate(void);

        template<typename T>
        void    mergeInsertAlgo(T &container);
        template<typename T>
        void    divideArray(T &container);
        template<typename T>
        void    insertionSortAlgo(T &array);
        template<typename T>
        void    mergeSort(T &leftArray, T &rightArray, T &finalArray);

        class IntOverflowException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };

        class InvalidArgumentException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };

        class EmptyArgumentException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };

        class NegatifNumberException : public std::exception
        {
            virtual const char *what() const throw();
        };

        class DuplicateFoundException : public std::exception
        {
            virtual const char *what() const throw();
        };


    private:
        std::list<int>      _finalLst;
        std::vector<int>    _tmpArg;
        std::deque<int>     _finalDeque;
        unsigned int        _kValue;
        double              _lstTime;
        double              _dequeTime;
};

#endif
