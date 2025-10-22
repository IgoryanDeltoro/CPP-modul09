#ifndef PMERGEME_TPP
#define PMERGEME_TPP
#include "PmergeMe.hpp"

// Default constractor 
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe() : _sortTime(0), _sorted(false), _debug(false) {}

// The parameterized constructor accepts an array of numbers with its lenth.
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(T *arr, int len) {
    for (size_t i = 0; i < static_cast<size_t>(len); i++) {
        long n = arr[i];
        if (n < 0 || n > INT_MAX)
            throw std::runtime_error("Error: Invalid number detected.");
        _data.push_back(n);
    }
    _sortTime = 0; 
    _sorted = false;
    _debug = false;
}

// The parameterized constructor accepts a container of numbers.
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(Container<T, std::allocator<T> > &arr) : _data(arr), _sortTime(0), _sorted(false), _debug(false) {}

// The Destructor
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::~PmergeMe() {}

// The function shows sequence of sorted and unsorted numbers. 
template <typename T, template <typename, typename> class Container>
void PmergeMe<T, Container>::displayData() {
    if (!_data.size())
        throw std::runtime_error("Error: There is no any data to display.");
    typename Container<T, std::allocator<T> >::iterator it = _data.begin();
    std::cout << (_sorted ? GREEN : YELLOW);
    std::cout << (_sorted ? "After" : "Before") << ":   ";
    for (; it != _data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << RESET << std::endl;
}

// The function shows the time spent on sorting.
template <typename T, template<typename, typename> class Container>
void PmergeMe<T, Container>::displaySortingTime() {
    std::string container_name = typeid(Container<T, std::allocator<T> >).name();
    size_t b = -1;
    if (!_sorted) {
        std::cout << MAGENTA << "The array has not been sorted yet."<< RESET << std::endl;
        return ;
    }
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

// Insertin array 
template <typename T, template <typename, typename> class Container>
template <typename Iterator>
void PmergeMe<T, Container>::insertNumbersArray(Iterator b, Iterator e) {
    _data.insert(_data.end(), b, e);
}

// Binary search
template <typename T, template < typename, typename > class Container>
int PmergeMe<T, Container>::binarySearch(Container<T, std::allocator<T> > &arr, T &value, int low, int high) {
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
void PmergeMe<T, Container>::fordJohnsonSort(Container<T, std::allocator<T> > &arr) {
    size_t num = arr.size();
    if (num <= 1) return;
    
    Container<std::pair<T, T>, std::allocator<std::pair<T, T> > > pairs;
    if (_debug) std::cout << "\nSwap the larger and smaller ones\n";
    for (size_t i = 0; (i + 1) < num; i += 2) {
        if (_debug) std::cout << "[" << arr[i] << "," << arr[i + 1] << "] ==> ";

        if (arr[i] > arr[i + 1]) {
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
            if (_debug) std::cout << "[" << arr[i + 1] << "," << arr[i] << "] \n";  
        } else {
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
            if (_debug) std::cout << "[" << arr[i] << "," << arr[i + 1] << "] \n";
        }
    }

    if (_debug) std::cout << "\nSorted by larger pairs\n";
    for (size_t s = 1; s < pairs.size(); ++s) {
        std::pair<T, T> key = pairs[s];
        int f = s - 1;
        while (f >= 0 && pairs[f].second > key.second) {
            pairs[f + 1] = pairs[f];
            f--;
        }
        pairs[f + 1] = key;
    }

    for (size_t i = 0; _debug && i < pairs.size(); i++){
        std::cout << "[" << pairs[i].first << "," << pairs[i].second << "] \n";
    }
    std::cout << (_debug ? "\n" : "");


    Container<T, std::allocator<T> > main, pendings;
    typename Container<std::pair<T, T>, std::allocator<std::pair<T, T> > >::iterator it;
    std::cout << (_debug ? "\nDevided each pair on main and pending chains\n" : "");
    it = pairs.begin();
    for (; it != pairs.end(); ++it) {
        pendings.push_back(it->first);
        main.push_back(it->second);
    }

    std::cout << (_debug ? "mainChain: \n" : "");
    for (size_t i = 0; _debug && i < main.size(); i++){
        std::cout << main[i] << " ";
    }
    std::cout << (_debug ? "\n" : "");
    std::cout << (_debug ? "pendingsChain: \n" : "");
    for (size_t i = 0; _debug && i < pendings.size(); i++){
        std::cout << pendings[i] << " ";
    }
    std::cout << (_debug ? "\n\n" : "");

    if (num % 2 != 0) {
        pendings.push_back(arr[num - 1]);
    }

    std::cout << (_debug ? "binary searching position: \n" : "");
    for (size_t i = 0; i < pendings.size(); ++i) {
        T selected = pendings[i];
        int pos = binarySearch(main, selected, 0, main.size() - 1);
        main.insert(main.begin() + pos, selected);
        if (_debug)std::cout  << "pos: " << pos << " element: " << selected << " ==> ";
        for (size_t i = 0; _debug && i < main.size(); i++)
            std::cout << main[i] << ",";
        std::cout << (_debug ? "\n" : "");
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
    if (_data.size() != 1)
        _sorted = true;
}

template <typename T, template < typename, typename > class Container>
void PmergeMe<T, Container>::debugMode(bool flag) {
    _debug = flag;
}

#endif