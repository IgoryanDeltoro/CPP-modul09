#include "PmergeMe.hpp"

size_t getLength(std::string str) {
    return str.length();
}

int main(int ac, char **av) {
    if (ac < 2) {
        std::cerr << "Error: Enter  ./PmergeMe 7 4 8 2 9\n";
        return 1;
    }

    // There is also debug mode that can be turn on by function 
    // or during compilation with option => make  MODE=debug 

    std::vector<int> v_arr; // vector container
    std::deque<int> d_arr; // deque container

    for (size_t i = 1; i < static_cast<size_t>(ac); i++) {
        char *pEnd;
        int n = static_cast<int>(std::strtod(av[i], &pEnd));
        if (!av[i][0] || getLength(pEnd) || n < 0 || n > INT_MAX) {
            std::cerr << "Error: Invalid number detected. \n";
            v_arr.clear();
            d_arr.clear();
            return 1;
        }
        v_arr.push_back(n);
        d_arr.push_back(n);
    }

    {
        try
        {
            PmergeMe<int, std::vector> v(v_arr);
            v.displayData();
            v.mergeInsertionSort(); // call fanction to sort numbers
            v.displayData(); 
            v.displaySortingTime();
        }
        catch(const std::exception& e)
        {
            std::cerr << RED << e.what() << RESET << '\n';
        }
    }
    
    {
        try
        {
            PmergeMe<int, std::deque> d;
            d.insertNumbersArray(d_arr.begin(), d_arr.end());
            d.displayData(); 
            d.mergeInsertionSort(); // call fanction to sort numbers
            d.displayData(); 
            d.displaySortingTime();
        }
        catch(const std::exception& e)
        {
            std::cerr << RED << e.what() << RESET << '\n';
        }
    }

    return 0;
}