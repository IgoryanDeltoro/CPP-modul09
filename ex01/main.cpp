#include "RPN.hpp"

int main(int ac, char **av) {

    if (ac != 2) {
        int i = 1;
        for (; i < ac; i++) {}
        if (i > 2) 
        std::cerr << "Error: Enter => ./RPN \"2 3 + 4 2 - *\"\n";
        return 1;
    }

    try
    {
        RPN rpn;
        rpn.calculateRPN(av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
