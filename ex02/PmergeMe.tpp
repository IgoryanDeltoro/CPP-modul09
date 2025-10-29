#include "PmergeMe.hpp"

// Default constractor 
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe() : _comparison_number(0), _sortTime(0), _sorted(false), _debug(DEBUG) {}

// The parameterized constructor accepts an array of numbers with its lenth.
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(T *arr, int len) {
    for (size_t i = 0; i < static_cast<size_t>(len); i++) {
        long n = arr[i];
        if (n < 0 || n > INT_MAX)
            throw std::runtime_error("Error: Invalid number detected.");
        _data.push_back(n);
    }
    _comparison_number = 0;
    _sortTime = 0; 
    _sorted = false;
    _debug = DEBUG;
}

// The parameterized constructor accepts a container of numbers.
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(Container<T, std::allocator<T> > &arr) :   _data(arr), 
                                                                            _comparison_number(0), 
                                                                            _sortTime(0), 
                                                                            _sorted(false), 
                                                                            _debug(DEBUG) {}

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
        std::cout << *it << ",";
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
    std::cout << " us " << RESET << "\n\n";
}

// ---------- Insertin array -------- 
template <typename T, template <typename, typename> class Container>
template <typename Iterator>
void PmergeMe<T, Container>::insertNumbersArray(Iterator b, Iterator e) {
    _data.insert(_data.end(), b, e);
}

 // -------- Binary Search --------
template <typename T, template <typename, typename> class Container>
int PmergeMe<T, Container>::binarySearch(Container<T, std::allocator<T> >& arr, T& value, int low, int high) {
    if (high <= low) {
        _comparison_number++;
        return (value > arr[low]) ? low + 1 : low;
    }
    int mid = (low + high) / 2;
    _comparison_number++;

    if (value == arr[mid])
        return mid + 1;
    else if (value > arr[mid])
        return binarySearch(arr, value, mid + 1, high);
    else
        return binarySearch(arr, value, low, mid - 1);
}

// -------- Generate Jacobsthal Sequence --------
std::vector<size_t> generateJacobsthalSequence(size_t n) {
    std::vector<size_t> seq;
    if (n == 0) return seq;

    size_t j0 = 0, j1 = 1;
    seq.push_back(1);
    while (true) {
        size_t next = j1 + 2 * j0;
        if (next > n)
            break;
        seq.push_back(next);
        j0 = j1;
        j1 = next;
    }
    return seq;
}

// --- Step 4: Insert pendings using Jacobsthal order ---
template <typename T, template <typename, typename> class Container>
void PmergeMe<T, Container>::handleJucobsthalRecurciveAlgorithm(Container<T, std::allocator<T> > &main, Container<T, std::allocator<T> > &pend) {
    if (pend.size() < 1)
        return ;
    std::vector<size_t> jacobSeq = generateJacobsthalSequence(pend.size());

    if (_debug) std::cout << "Inserting in Jacobsthal order:\n";
    for (size_t j = 0; j < jacobSeq.size(); ++j) {
        size_t idx = (jacobSeq[j] < jacobSeq.size()) ? jacobSeq[j] - 1 : j;
        if (idx >= pend.size()) continue;

        T selected = pend[idx];
        int pos = binarySearch(main, selected, 0, main.size() - 1);
        main.insert(main.begin() + pos, selected);
        pend.erase(pend.begin() + idx);

        if (_debug) {
            std::cout << "insert pendings[" << jacobSeq[j] << " - 1]=" << selected
                << " at pos " << pos << " => ";
            for (size_t k = 0; k < main.size(); k++) std::cout << main[k] << ",";
            std::cout << "\n";
        }
    }
    handleJucobsthalRecurciveAlgorithm(main, pend);
}

// -------- Ford–Johnson Sort --------
template <typename T, template <typename, typename> class Container>
void PmergeMe<T, Container>::fordJohnsonSort(Container<T, std::allocator<T> >& arr) {
    size_t num = arr.size();
    if (num <= 1) return;

    // --- Step 1: Pairing and swapping ---
    Container<std::pair<T, T>, std::allocator<std::pair<T, T> > > pairs;
    if (_debug) std::cout << "\nPairing and swapping\n";
    for (size_t i = 0; (i + 1) < num; i += 2) {
        if (_debug) std::cout << "[" << arr[i] << "," << arr[i + 1] << "] ==> ";
        if (arr[i] > arr[i + 1]) {
            _comparison_number++;
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
            if (_debug) std::cout << "[" << arr[i + 1] << "," << arr[i] << "] \n";
        } else {
            _comparison_number++;
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
            if (_debug) std::cout << "[" << arr[i] << "," << arr[i + 1] << "] \n";
        }
    }

    // --- Step 2: Sort pairs by larger element ---
    if (_debug) std::cout << "\nSorting by larger elements:\n";
    for (size_t s = 1; s < pairs.size(); ++s) {
        std::pair<T, T> key = pairs[s];
        int f = s - 1;
        while (f >= 0 && pairs[f].second > key.second) {
            _comparison_number++;
            pairs[f + 1] = pairs[f];
            f--;
        }
        pairs[f + 1] = key;
    }
    if (_debug) {
        for (size_t i = 0; i < pairs.size(); i++)
            std::cout << "[" << pairs[i].first << "," << pairs[i].second << "] ";
        std::cout << "\n";
    }

    // --- Step 3: Split into main and pending chains ---
    Container<T, std::allocator<T> > mainChain, pendingsChain;
    typename Container<std::pair<T, T>, std::allocator<std::pair<T, T> > >::iterator it;
    for (it = pairs.begin(); it != pairs.end(); ++it) {
        pendingsChain.push_back(it->first);
        mainChain.push_back(it->second);
    }

    // Handle odd element
    if (num % 2 != 0)
        pendingsChain.push_back(arr[num - 1]);

    if (_debug) {
        std::cout << "\nMain chain: ";
        for (size_t i = 0; i < mainChain.size(); i++) std::cout << mainChain[i] << ",";
        std::cout << "\nPendings chain: ";
        for (size_t i = 0; i < pendingsChain.size(); i++) std::cout << pendingsChain[i] << ",";
        std::cout << "\n\n";
    }

    // --- Step 4: Call recurcive Insert pendings using Jacobsthal order ---
    handleJucobsthalRecurciveAlgorithm(mainChain, pendingsChain);

    arr.swap(mainChain);
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
    if (_debug) std::cout << "Number of comparisons are => " << _comparison_number << std::endl;
}

template <typename T, template < typename, typename > class Container>
void PmergeMe<T, Container>::debugMode(bool flag) {
    _debug = flag;
}
