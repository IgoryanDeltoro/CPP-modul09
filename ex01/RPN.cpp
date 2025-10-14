#include "RPN.hpp"

RPN::RPN() {}
RPN::~RPN() {}

int handleCanculation(int f, int l, int oper) {
    switch (oper)
    {
    case 43:
        return f + l;   
    case 45:
        return f - l;
    case 47:
        return f / l; 
    case 42:
        return f * l;
    }
    return 0;
}

bool isOperator(std::string oper) {
    if (oper == "+" || oper == "-" || oper == "*" ||oper == "/")
        return true;
    return false;
}

size_t getLength(std::string str) {
    return str.length();
}

bool isRightOperatorNum(const std::string &str) {
    std::stringstream ss(str);
    std::string token;
    int operators = 0;
    int digits = 0;

    while (ss >> token) {
        if (isOperator(token))
            operators++;
        else
            digits++; 
    }
    return ((digits - operators) == 1);
}

void RPN::calculateRPN(const std::string &rpn) {
    if (rpn.empty() || !isRightOperatorNum(rpn))
        throw std::runtime_error("Error: incorrect numbers of operators.");

    std::stringstream ss(rpn);
    std::string token;

    while (ss >> token) {
        char* pEnd = NULL;
        int d = static_cast<int>(std::strtod(token.c_str(), &pEnd));
        if (d > 9)
            throw std::runtime_error("Error: Typed element < " + token + " > should be less then 10.");
        if (!isOperator(token) && getLength(pEnd)) {
            throw std::runtime_error(("Error: Incorrect digit < " + token + " >"));
        }
            
        if (!isOperator(token)) {
            _digit.push(d);
        } else {
            int first = _digit.top();
            _digit.pop();
            int last = _digit.top();
            _digit.pop();
            int result = handleCanculation(last, first, token[0]);
            _digit.push(result);
        }
    }
    std::cout << _digit.top() << std::endl;
}
