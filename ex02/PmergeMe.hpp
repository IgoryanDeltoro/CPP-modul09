#ifndef PMERGEME_HPP
#define PMERGEME_HPP
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
        void mergeInsertionSorting();
        void displayUnsortedNumbers();
        void displaySortedNumbers();
        void displaySortingTime();
};

#include "PmergeMe.tpp"

#endif