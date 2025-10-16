#include "PmergeMe.hpp"

size_t getLength(std::string str) {
    return str.length();
}

int main(int ac, char **av) {
    if (ac == 1) {
        std::cerr << "Error: Enter  ./pmergeme 7 4 8 2 9\n";
        return 1;
    }

    std::vector<int> v_arr; // vector container
    std::vector<int> d_arr; // deque container

    for (size_t i = 1; i < ac; i++) {
        char *pEnd;
        int n = static_cast<int>(std::strtod(av[i], &pEnd));
        if (getLength(pEnd) || n < INT_MIN || n > INT_MAX) {
            std::cerr << "Error: Incorect number foud. \n";
            v_arr.clear();
            d_arr.clear();
            return 1;
        }
        v_arr.push_back(n);
        d_arr.push_back(n);
    }

    std::cout << "\n=========== sort test by vector container\n\n";
    PmergeMe<int, std::vector> v;
    v.insertNumbersArray(v_arr.begin(), v_arr.end());
    v.mergeInsertionSort();
    v.displayArray();

    std::cout << "\n=========== sort test by deque container\n\n";
    PmergeMe<int, std::deque> d;
    d.insertNumbersArray(d_arr.begin(), d_arr.end());
    d.mergeInsertionSort();
    d.displayArray();


    return 0;
}