#ifndef PMERGEME_HPP
#define PMERGEME_HPP

# ifndef DEBUG
# define DEBUG false
# endif

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
#include <cstdlib>
#include <typeinfo>

template <typename T, template <typename, typename> class Container> class PmergeMe {
    private:
        Container<T, std::allocator<T> > _data;
        double  _sortTime;
        bool    _sorted;
        bool     _debug;

        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);

        void fordJohnsonSort(Container<T, std::allocator<T> > &arr);
        int binarySearch(Container<T, std::allocator<T> > &arr, T &value, int low, int high);

    public:
        PmergeMe();
        PmergeMe(T *arr, int len);
        PmergeMe(Container<T, std::allocator<T> > &arr);
        ~PmergeMe();

        template <typename Iterator>
        void insertNumbersArray(Iterator b, Iterator e);
        void mergeInsertionSort();
        void displayData();
        void displaySortingTime();
        void debugMode(bool flag = true);
};

#include "PmergeMe.tpp"

#endif