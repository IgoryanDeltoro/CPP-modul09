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
int binarySearch(Container<T, std::allocator<T>> &arr, T &value, int low, int high) {
    if (high <= low)
        return (value > arr[low]) ? low + 1 : low;
        
    int mid = (low + high) / 2;

    if (value == arr[mid])
        return (mid + 1);
    
    if (value > arr[mid])
        return binarySearch(arr, value, mid + 1, high);
    
    return binarySearch(arr, value, low, mid - 1);
}

template <typename T, template < typename, typename > class Container>
void fordJohnsonSort(Container<T, std::allocator<T>> &arr) {
    size_t num = arr.size();
    if (num <= 2) return;
    
    Container<std::pair<T, T>, std::allocator<std::pair<T, T>>> pairs;
    for (size_t i = 0; (i + 1) < num; i += 2) {
        if (arr[i] > arr[i + 1])
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
        else
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
    }
    
    for (size_t s = 1; s < pairs.size(); ++s) {
        std::pair<T, T> key = pairs[s];
        int f = s - 1;
        while (f >= 0 && pairs[f].second > key.second) {
            pairs[f + 1] = pairs[f];
            f--;
        }
        pairs[f + 1] = key;
    }

    Container<T, std::allocator<T>> main, pendings;
    typename Container<std::pair<T, T>, std::allocator<std::pair<T, T>>>::iterator it = pairs.begin();
    for (; it != pairs.end(); ++it) {
        pendings.push_back(it->first);
        main.push_back(it->second);
    }

    if (num % 2 != 0) {
        pendings.push_back(arr[num - 1]);
    }

    for (size_t i = 0; i < pendings.size(); ++i) {
        T selected = pendings[i];
        int pos = binarySearch(main, selected, 0, main.size() - 1);
        main.insert(main.begin() + pos, selected);
    }

    arr.swap(main);
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