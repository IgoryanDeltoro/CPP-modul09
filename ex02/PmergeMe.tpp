#ifndef PMERGEME_TPP
#define PMERGEME_TPP
#include "PmergeMe.hpp"

template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe() : _sortTime(0) {}

template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::~PmergeMe() {}

template <typename T, template <typename, typename> class Container>
void PmergeMe<T, Container>::displayUnsortedNumbers() {
    if (!_data.size())
        throw std::runtime_error("Error: There is no any data to display.");
    typename Container<T, std::allocator<T>>::iterator it = _data.begin();
    std::cout << "Before:   ";
    for (; it != _data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename T, template <typename, typename> class Container>
void PmergeMe<T, Container>::displaySortedNumbers() {
    if (!_data.size())
        throw std::runtime_error("Error: There is no any data to display.");
    typename Container<T, std::allocator<T>>::iterator it = _data.begin();
    std::cout << "After:   ";
    for (; it != _data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename T, template<typename, typename> class Container>
void PmergeMe<T, Container>::displaySortingTime() {
    std::cout << "Time to process a range of " << _data.size();
    std::cout << " elements with : " << std::fixed 
    << _sortTime << std::setprecision(5);
    std::cout << " sec " << std::endl;
}

template <typename T, template <typename, typename> class Container>
template <typename Iterator>
void PmergeMe<T, Container>::insertNumbersArray(Iterator b, Iterator e) {
    _data.insert(_data.end(), b, e);
}

template <typename T, template < typename, typename > class Container>
void bineryInsertion(Container<T, std::allocator<T>> &arr, T &value) {
    typename Container<T, std::allocator<T>>::iterator p;
    p = std::lower_bound(arr.begin(), arr.end(), value);
    arr.insert(p, value);
}

template <typename T, template < typename, typename > class Container>
void fordJohnsonSort(Container<T, std::allocator<T>> &arr) {
    size_t num = arr.size();
    if (num <= 1) return;
    
    Container<T, std::allocator<T>> small;
    Container<T, std::allocator<T>> larg;

    for (size_t f = 0; (f + 1) < num; f += 2) {
        int s = f + 1;
        if (arr[f] > arr[s]) {
            small.push_back(arr[s]);
            larg.push_back(arr[f]);
        } else {
            small.push_back(arr[f]);
            larg.push_back(arr[s]);
        }
    }

    if (num % 2 != 0) {
        small.push_back(arr[num - 1]);
    }

    fordJohnsonSort(larg);

    for (size_t i = 0; i < small.size(); i++) {
        bineryInsertion(larg, small[i]);
    }
    
    arr = larg;
}

template <typename T, template < typename, typename > class Container>
void PmergeMe<T, Container>::mergeInsertionSorting() {
    clock_t start, end;

    start = clock();
    fordJohnsonSort(_data);
    end = clock();
    _sortTime = double(end - start) / double(CLOCKS_PER_SEC);

}

#endif