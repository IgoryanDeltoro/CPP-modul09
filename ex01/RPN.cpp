#include "RPN.hpp"

RPN::RPN() {}
RPN::~RPN() {}

int handleCanculation(int f, int s, int oper) {
    switch (oper)
    {
    case 43:
        return f + s;   
    case 45:
        return f - s;
    case 47:
        return f / s; 
    case 42:
        return f * s;
    default:
        return -1;
        break;
    }
    return -1;
}

void RPN::calculateRPN(const std::string &rpn) {
    if (rpn.empty())
        return;
    
    for (size_t i = 0; i < rpn.size(); i++) {
        if (!std::strchr("0123456789+-*/ ", rpn[i]))
            throw std::runtime_error("Error: incorrect element was found.");
        if (std::isdigit(rpn[i])) {
            int d = rpn[i] - 48;
            if (d < 0 || d > 9) {
                throw std::runtime_error("Error: incorrect integer.");
            }
            _digit.push_back(d);
        } else {
            if (rpn[i] == 32 || rpn[i] == 9) continue;
            int first, last;
            first = _digit.front();
            last = _digit.back();
            if (_digit.size() != 2)
                throw std::runtime_error("Error: There is an extra operator.");

            int result = handleCanculation(first, last, rpn[i]);
            _digit.pop_front();
            _digit.pop_back();
            _digit.push_back(result);
        }
    }
    std::cout << _digit.front() << std::endl;
}