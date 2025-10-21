#ifndef PMERGEME_HPP
#define PMERGEME_HPP
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define MAGENTA "\e[35m"
# define RESET "\e[0m"
#include <iostream>
#include <sstream>
#include <climits>
#include <vector>
#include <deque>
#include <ctime>
#include <iomanip>
#include <utility>
#include <map>

template <typename T, template <typename, typename> class Container> class PmergeMe {
    private:
        Container<T, std::allocator<T>> _data;
        double _sortTime;

        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);

    public:
        PmergeMe();
        ~PmergeMe();

        template <typename Iterator>
        void insertNumbersArray(Iterator b, Iterator e);
        void mergeInsertionSort();
        void displayData(bool flag = false);
        void displaySortingTime();
};

#include "PmergeMe.tpp"

#endif