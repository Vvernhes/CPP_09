#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) { }

PmergeMe::PmergeMe(const PmergeMe& src)
{
    *this = src;
}

PmergeMe::~PmergeMe(void) { }

PmergeMe    &PmergeMe::operator=(const PmergeMe &rhs)
{

    if (this != &rhs)
    {
        this->_finalLst = rhs._finalLst;
        this->_finalDeque = rhs._finalDeque;
        this->_tmpArg = rhs._tmpArg;
        this->_kValue = rhs.getKValue();
        this->_lstTime = rhs._lstTime;
        this->_dequeTime = rhs._dequeTime;
    }
    return (*this);
}


template<typename T>
void    PmergeMe::check_arg(T &container, const char *arg)
{
    long    tmp;
    char    *p_end;

    if (*arg == '\0')
        throw EmptyArgumentException();
    while (*arg != '\0')
    {
        tmp = std::strtol(arg, &p_end, 10);
        if (arg == p_end)
        {
            if (std::isspace(static_cast<unsigned char>(*arg)))
                arg++;
            else if (*arg < '0' || *arg > '9')
                throw InvalidArgumentException();
        }
        else
        {
            if (tmp > INT_MAX)
                throw IntOverflowException();
            else if (tmp < 0)
                throw NegatifNumberException();
            container.push_back(static_cast<int>(tmp));
            arg = p_end;
        }
    }
}

template<typename T>
void    PmergeMe::displayContainer(const T &container)
{
    typename T::const_iterator it;

    it = container.begin();
    while(it != container.end())
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl;
}

void    PmergeMe::setKValue(void)
{
    double  nbElem;
    double  kV;

    nbElem = _tmpArg.size();
    kV = sqrt(nbElem);
    kV = modf(kV, &nbElem);
    if (kV > 0.5)
        nbElem++;
    _kValue = static_cast<unsigned int>(nbElem);
}

int     PmergeMe::getKValue(void) const
{
    return (_kValue);
}

void    PmergeMe::checkDuplicate(void)
{
    std::vector<int>::iterator it = _tmpArg.begin();
    std::vector<int>::iterator next;

    if (_tmpArg.size() == 0)
        throw EmptyArgumentException();
    while (it != _tmpArg.end())
    {
        next = it;
        next++;
        while (next != _tmpArg.end())
        {
            if (*it == *next)
            {
                throw DuplicateFoundException();
            }
            next++;
        }
        it++;
    }
}

void    PmergeMe::start(char **argv, int argc)
{
    for (int i = 1; i < argc; i++)
    {
        check_arg(_tmpArg, argv[i]);
    }
    checkDuplicate();
    setKValue();
    launchList();
    launchDeque();
    std::cout << "Before : ";
    displayContainer(_tmpArg);
    std::cout << "After : ";
    displayContainer(_finalDeque);
    std::cout << "Time to process a range of " << _tmpArg.size() << " elements with std::list  : " << _lstTime << " ms\n";
    std::cout << "Time to process a range of " << _tmpArg.size() << " elements with std::deque : " << _dequeTime << " ms" << std::endl;
}

void    PmergeMe::launchList(void)
{
    std::clock_t start;
    std::clock_t end;

    _finalLst.assign(_tmpArg.begin(), _tmpArg.end());
    start = std::clock();
    mergeInsertAlgo<std::list<int> >(_finalLst);
    end = std::clock();
    _lstTime = 1000.0 * (end - start) / CLOCKS_PER_SEC;
}

void    PmergeMe::launchDeque(void)
{

    std::clock_t start;
    std::clock_t end;

    _finalDeque.assign(_tmpArg.begin(), _tmpArg.end());
    start = std::clock();
    mergeInsertAlgo<std::deque<int> >(_finalDeque);
    end = std::clock();
    _dequeTime = 1000.0 * (end - start) / CLOCKS_PER_SEC;
}

template<typename T>
void    PmergeMe::mergeInsertAlgo(T &container)
{
    if (container.size() <= _kValue)
    {
        insertionSortAlgo(container);
        return;
    }
    else
    {
        unsigned int half = container.size() / 2;
        T leftArray;
        T rightArray;
        typename T::iterator it = container.begin();

        for (unsigned int i = 0; i < half; i++)
        {
            leftArray.push_back(*it);
            it++;
        }
        while (it != container.end())
        {
            rightArray.push_back(*it);
            it++;
        }
        container.clear();
        mergeInsertAlgo(rightArray);
        mergeInsertAlgo(leftArray);
        mergeSort(leftArray, rightArray, container);
    }
}

template<typename T>
void    PmergeMe::insertionSortAlgo(T &array)
{
    typename T::iterator     firstIt = array.begin();
    typename T::iterator     nextIt = firstIt;

    nextIt++;
    while (nextIt != array.end())
    {
        if (*firstIt > *nextIt)
        {
            int tmp = *firstIt;
            *firstIt = *nextIt;
            *nextIt = tmp;
            if (firstIt != array.begin())
            {
                firstIt--;
                nextIt--;
            }
        }
        else
        {
            firstIt++;
            nextIt++;
        }
    }
}

template<typename T>
void    PmergeMe::mergeSort(T &leftArray, T &rightArrray, T &finalArray)
{
    typename T::iterator leftIt = leftArray.begin();
    typename T::iterator rightIt = rightArrray.begin();

    while (leftIt != leftArray.end() && rightIt != rightArrray.end())
    {
        if (*leftIt <= *rightIt)
        {
            finalArray.push_back(*leftIt);
            leftIt++;
        }
        else
        {
            finalArray.push_back(*rightIt);
            rightIt++;
        }
    }
    while (leftIt != leftArray.end())
    {
        finalArray.push_back(*leftIt);
        leftIt++;
    }
    while (rightIt != rightArrray.end())
    {
        finalArray.push_back(*rightIt);
        rightIt++;
    }
}

const char *PmergeMe::IntOverflowException::what() const throw()
{
    return ("Int Overflow");
}

const char *PmergeMe::NegatifNumberException::what() const throw()
{
    return ("Negatif number are not accepted");
}

const char *PmergeMe::InvalidArgumentException::what() const throw()
{
    return ("Invalid argument pass");
}

const char *PmergeMe::DuplicateFoundException::what() const throw()
{
    return ("Duplicate found");
}

const char *PmergeMe::EmptyArgumentException::what() const throw()
{
    return ("Empty argument passed");
}