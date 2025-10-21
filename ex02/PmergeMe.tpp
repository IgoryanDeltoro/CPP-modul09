#ifndef PMERGEME_TPP
#define PMERGEME_TPP
#include "PmergeMe.hpp"

template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe() : _sortTime(0) {}

template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::~PmergeMe() {}

template <typename T, template <typename, typename> class Container>
void PmergeMe<T, Container>::displayData(bool flag) {
    if (!_data.size())
        throw std::runtime_error("Error: There is no any data to display.");
    typename Container<T, std::allocator<T>>::iterator it = _data.begin();
    std::cout << (flag ? GREEN : YELLOW);
    std::cout << (flag ? "After" : "Before") << ":   ";
    for (; it != _data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << RESET << std::endl;
}

template <typename T, template<typename, typename> class Container>
void PmergeMe<T, Container>::displaySortingTime() {
    std::string container_name = typeid(Container<T, std::allocator<T>>).name();
    size_t b = -1;
    if ((b = container_name.find("vector")) != std::string::npos)
        container_name = "std::vector<int>";
    else if (container_name.find("vector"))
        container_name = "std::deque<int>";
    else 
        container_name = "std::unknown_container";

    std::cout << MAGENTA << "Time to process a range of " << _data.size();
    std::cout << " elements with " << container_name
    << ": " << std::fixed << _sortTime << std::setprecision(5);
    std::cout << " us " << RESET << std::endl;
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
    std::cout << "\nSwap the larger and smaller ones\n";
    for (size_t i = 0; (i + 1) < num; i += 2) {
        std::cout << "[" << arr[i] << "," << arr[i + 1] << "] ==> ";

        if (arr[i] > arr[i + 1]) {
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
            std::cout << "[" << arr[i + 1] << "," << arr[i] << "] \n";  
        } else {
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
            std::cout << "[" << arr[i] << "," << arr[i + 1] << "] \n";
        }
    }

    std::cout << "\nSorted by larger pairs\n";
    for (size_t s = 1; s < pairs.size(); ++s) {
        std::pair<T, T> key = pairs[s];
        int f = s - 1;
        while (f >= 0 && pairs[f].second > key.second) {
            pairs[f + 1] = pairs[f];
            f--;
        }
        pairs[f + 1] = key;
    }

    for (size_t i = 0; i < pairs.size(); i++){
        std::cout << "[" << pairs[i].first << "," << pairs[i].second << "] \n";
    }
    std::cout << "\n";


    Container<T, std::allocator<T>> main, pendings;
    typename Container<std::pair<T, T>, std::allocator<std::pair<T, T>>>::iterator it;
    std::cout << "\nDevided each pair on main and pending chains\n";
    it = pairs.begin();
    for (; it != pairs.end(); ++it) {
        pendings.push_back(it->first);
        main.push_back(it->second);
    }
    std::cout << "mainChain: \n";
    for (size_t i = 0; i < main.size(); i++){
        std::cout << main[i] << " ";
    }
    std::cout << "\n";
    std::cout << "pendingsChain: \n";
    for (size_t i = 0; i < pendings.size(); i++){
        std::cout << pendings[i] << " ";
    }
    std::cout << "\n\n";

    if (num % 2 != 0) {
        pendings.push_back(arr[num - 1]);
    }

    std::cout << "binary searching position: \n";
    for (size_t i = 0; i < pendings.size(); ++i) {
        T selected = pendings[i];
        int pos = binarySearch(main, selected, 0, main.size() - 1);
        main.insert(main.begin() + pos, selected);
        std::cout  << "pos: " << pos << " element: " << selected << " ==> ";
        for (size_t i = 0; i < main.size(); i++)
            std::cout << main[i] << ",";
        std::cout << std::endl;
    }

    arr.swap(main);
}

template <typename T, template < typename, typename > class Container>
void PmergeMe<T, Container>::mergeInsertionSort() {
    clock_t start, end;

    start = clock();
    fordJohnsonSort(_data);
    end = clock();
    _sortTime = double(end - start) / double(CLOCKS_PER_SEC);
}

#endif