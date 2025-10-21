#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <sstream>
#include <stack>
#include <list>
#include <cstdlib>
#include <cstring>
#include <climits>

class RPN {
    private:
        std::stack<long, std::list<long> > _digit;

        RPN(const RPN &other);
        RPN &operator=(const RPN &other);

    public:
        RPN();
        ~RPN();

        void calculateRPN(const std::string &rpn);
};

#endif