#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <list>
#include <cstdlib>
#include <cstring>

class RPN {
    private:
        std::list<int> _digit;

        RPN(const RPN &other);
        RPN &operator=(const RPN &other);

    public:
        RPN();
        ~RPN();

        void calculateRPN(const std::string &rpn);
};

#endif