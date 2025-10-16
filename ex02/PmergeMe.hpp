#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <sstream>
#include <climits>
#include <vector>
#include <deque>

template <typename T, template <typename, typename> class Container> class PmergeMe {
    private:
        Container<T, std::allocator<T>> _data;

        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);

    public:
        PmergeMe();
        ~PmergeMe();

        template <typename Iterator>
        void insertNumbersArray(Iterator b, Iterator e);
        void mergeInsertionSort();
        void displayArray();
};

#include "PmergeMe.tpp"

#endif