#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

void openFile(std::ifstream &file, const std::string &input) {
    file.open(input.c_str());
    if (!file.is_open())
        throw std::logic_error("Error: Unable to open " + input);
}

bool validateDate(const std::string &date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    int y = std::atoi(date.substr(0, 4).c_str());
    int m = std::atoi(date.substr(5, 2).c_str());
    int d = std::atoi(date.substr(8, 2).c_str());
    return (y >= 2000 && m >= 1 && m <= 12 && d >= 1 && d <= 31);
}

bool validateValue(const std::string &str, double &value) {
    if (str.empty())
        return false;
    std::stringstream ss(str);
    ss >> value;
    return (ss.fail() && value > 0 && value <= 1000);
}

void BitcoinExchange::findBtcRate(const std::string &input) {
    std::ifstream file;
    openFile(file, input);

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        std::stringstream ss(line);
        std::string date, pipe, value;
        ss >> date >> pipe >> value;
        std::cout << "date: " << date << "  value: " << value << std::endl;

        if (!validateDate(date)) {
            std::cout << "Error: : bad input => " << date << std::endl; 
        }
        double in_value;
        if (!validateValue(date, in_value)) {
            std::cout << "Error: : bad input => " << date << std::endl; 
        }
    }
}

void BitcoinExchange::getDataFromDB(const std::string &input) {
    std::ifstream file;
    openFile(file, input);

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, value;
        if (std::getline(ss, date, ',') && std::getline(ss, value)) {
            _database[date] = std::atof(value.c_str());
        }
    }
}

// std::ostream& operator<<(std::ostream &os, BitcoinExchange &btc) {
//     std::map<std::string, float>::iterator it;
//     for (it = btc.data().begin() ; it != btc.data().end(); ++it) {
//         os << "date: " << it->first << "  value: " << it->second << std::endl;
//     }
//     return os;
// }
