#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

bool isDigit(const std::string &str, char exeption);
void openFile(std::ifstream &file, const std::string &input);
bool validateDate(const std::string &date);
bool validateValue(const std::string &str, double &value);
void trim(std::string &input);

void BitcoinExchange::findBtcRate(const std::string &input) {
    std::ifstream file;
    openFile(file, input);
    bool is_header = false;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            std::cout << "Error: bad input => empty line\n";
            continue;
        }

        std::stringstream ss(line);
        std::string date, delim, value, extra;
        ss >> date >> delim >> value >> extra;

        if (!is_header) {
            if (date == "date" && delim == "|" && value == "value")
                is_header = !is_header;
            else
                throw std::runtime_error("Error: Invalid header in the imput file.");
            continue;
        }

        if (!extra.empty() || delim != "|" || !validateDate(date)) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        double in_value;
        if (!validateValue(value, in_value)) {
            if (in_value < 0)
                std::cout << "Error: not a positive number.\n";
            else
                std::cout << "Error: too large a number.\n";
            continue;
        }

        if(!isDigit(value, '.')) {
            std::cout << "Error: wrong value \"" << value << "\".\n";
            continue;
        }

        std::map<std::string, double>::const_iterator it = _database.lower_bound(date);
        if (it == _database.end() || it->first != date) {
            if (it == _database.begin()) {
                std::cout << "Error: no earlier date in database." << it->first << '\n';
                continue;
            }
            --it;
        }
        double btc_rate = it->second * in_value;
        std::cout << date << " => " << value << " = "<< btc_rate << std::endl;
    }
}

void validateLine(const std::string &line) {
    if (line.empty())
        throw std::runtime_error("Error: database has wrong data.");
}

void BitcoinExchange::getDataFromDB(const std::string &input) {
    std::ifstream file;
    openFile(file, input);

    std::string line;
    std::getline(file, line);
    trim(line);
    if (line != "date,exchange_rate")
        throw std::runtime_error("Error: database has wrong data.");
    while (std::getline(file, line)) {
        trim(line);
        validateLine(line);
        std::stringstream ss(line);
        std::string date, value;
        if (std::getline(ss, date, ',') && std::getline(ss, value))
            _database[date] = std::atof(value.c_str());
        if (line[10] != ',' || !validateDate(date) || !isDigit(value, '.'))
            throw std::runtime_error("Error: database has wrong data.");
    }
}

bool isDigit(const std::string &str, char exeption) {
    if (str.empty())
        return false;
    for (size_t i = 0; i < str.length(); i++) {
        if (exeption != 48 && exeption == str[i])
            continue;
        if (!std::isdigit(str[i]))
            return false;
    }
    return true;
}

void openFile(std::ifstream &file, const std::string &input) {
    file.open(input.c_str());
    if (!file.is_open())
        throw std::logic_error("Error: Unable to open " + input);
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool validateDate(const std::string &date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-' || !isDigit(date, '-'))
        return false;
    int y = std::atoi(date.substr(0, 4).c_str());
    int m = std::atoi(date.substr(5, 2).c_str());
    int d = std::atoi(date.substr(8, 2).c_str());

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(y)) 
        daysInMonth[1] = 29;

    return (y >= 2009 && (m >= 1 && m <= 12) && (d >= 1 && d <= daysInMonth[m - 1]));
}

bool validateValue(const std::string &str, double &value) {
    if (str.empty())
        return false;
    std::size_t p = str.find(".");
    std::stringstream ss(str);
    ss >> value;
    return ((value > 0 && value <= 1000) && str.length() - p <= 13);
}

void trim(std::string &str) {
    std::string::iterator start = str.begin(), stop = str.end();
    while (start != stop && (*start == 32 || *start == 9)) ++start;
    if (start == stop) {
        str.clear();
    } else {
        while (start != --stop && (*stop == 32 || *stop == 9)) ; 
        ++stop;

        str.erase(stop, str.end());
        str.erase(str.begin(), start);
    }
}
