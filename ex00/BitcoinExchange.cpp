#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

bool isDigit(const std::string &str, char exeption);
void openFile(std::ifstream &file, const std::string &input);
bool validateDate(const std::string &date);
bool validateValue(const std::string &str, bool isDB);
void trim(std::string &input);

void BitcoinExchange::findBtcRate(const std::string &input) {
    std::ifstream file;
    openFile(file, input);
    bool is_header = false;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            std::cout << "Error: bad input => empty line" << std::endl;
            continue;
        }

        std::stringstream ss(line);
        std::string date, delim, value, extra;
        ss >> date >> delim >> value >> extra;

        if (!is_header) {
            if (date == "date" && delim == "|" && value == "value" && extra.empty())
                is_header = !is_header;
            else
                throw std::runtime_error("Error: Invalid header in the input file.");
            continue;
        }

        if (!extra.empty() || delim != "|" || !validateDate(date)) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (value.empty()) {
            std::cout << "Error: bad input => value is empty." << std::endl;
            continue;
        }

        if (!validateValue(value, true)) {
            std::cout << "Error: bad input => " << value << std::endl;
            continue;
        }

        double in_value = std::strtod(value.c_str(), NULL);
        if (in_value < 0) {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }

        if (in_value > 1000) {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        if(!isDigit(value, '.')) {
            std::cout << "Error: wrong value " << value << std::endl;
            continue;
        }

        std::map<std::string, double>::const_iterator it = _database.lower_bound(date);
        if (it == _database.end() || it->first != date) {
            if (it == _database.begin()) {
                std::cout << "Error: no earlier date in database " << it->first << std::endl;
                continue;
            }
            --it;
        }
        double btc_rate = it->second * in_value;
        std::cout << date << " => " << value << " = "<< btc_rate << std::endl;
    }
    if (!is_header)
        throw std::runtime_error("Error: Invalid header in the input file.");
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
        if (line[10] != ',' || !validateDate(date) || !isDigit(value, '.') || !validateValue(value, false))
            throw std::runtime_error("Error: database has wrong data.");
    }
    if (_database.empty())
        throw std::runtime_error("Error: database has wrong data.");
}

bool isDigit(const std::string &str, char exeption) {
    if (str.empty())
        return false;
    for (size_t i = 0; i + 1 < str.length(); i++) {
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

    time_t t = time(NULL);
    tm *now = localtime(&t);

    int curr_y = now->tm_year + 1900;
    int curr_m = now->tm_mon + 1;
    int curr_d = now->tm_mday;

    int y = std::atoi(date.substr(0, 4).c_str());
    int m = std::atoi(date.substr(5, 2).c_str());
    int d = std::atoi(date.substr(8, 2).c_str());
    
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(y)) 
        daysInMonth[1] = 29;

    bool isVY = !(y > curr_y);
    bool isVM = !(y == curr_y && m > curr_m);
    bool isVD = !(y == curr_y && m == curr_m && d > curr_d);

    return ((y >= 2009 && isVY) && ((m >= 1 && m <= 12) && isVM) && ((d >= 1 && d <= daysInMonth[m - 1]) && isVD));
}

bool validateValue(const std::string &str, bool isDB) {
    bool dotSeen = false;
    if (str[0] == '.' || str[str.length() -1] == '.')
        return false;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '.') {
            if (i == 0 || !isdigit(str[i + 1])) return false; 
            if (dotSeen) return false; 
            dotSeen = true;
        }
    }
    if (isDB && str.find("1000") == 0) {
        size_t dotPos = str.find('.');
        if (dotPos != std::string::npos) {
            for (size_t i = dotPos + 1; i < str.size(); ++i) {
                if (str[i] != '0') {
                    return false;
                }
            }
        }
    }
    return true;
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
