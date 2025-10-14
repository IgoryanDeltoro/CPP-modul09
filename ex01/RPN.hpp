#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <sstream>
#include <stack>
#include <cstdlib>
#include <cstring>

class RPN {
    private:
        std::stack<int> _digit;

        RPN(const RPN &other);
        RPN &operator=(const RPN &other);

    public:
        RPN();
        ~RPN();

        void calculateRPN(const std::string &rpn);
};

#endif