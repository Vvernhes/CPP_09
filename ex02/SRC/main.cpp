#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "PmergeMe.hpp"

int main (int argc, char **argv)
{
    PmergeMe    algo;

    if (argc < 2)
    {
        std::cerr << "Error: Wrong number of arguments." << std::endl;
        return (1);
    }
    else
    {
        try
        {
            algo.start(argv, argc);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return (2);
        }
    }
}