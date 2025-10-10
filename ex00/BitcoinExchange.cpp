#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

void openFile(std::ifstream &file, const std::string &input) {
    file.open(input.c_str());
    if (!file.is_open())
        throw std::logic_error("Error: Unable to open " + input);
}

bool validateDate(const std::string &date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    int y = std::atoi(date.substr(0, 4).c_str());
    int m = std::atoi(date.substr(5, 2).c_str());
    int d = std::atoi(date.substr(8, 2).c_str());
    return (y >= 2000 && (m >= 1 && m <= 12) && (d >= 1 && d <= 31));
}

bool validateValue(const std::string &str, double &value) {
    if (str.empty())
        return false;
    std::stringstream ss(str);
    ss >> value;
    return ((value > 0 && value <= 1000));
}

void BitcoinExchange::findBtcRate(const std::string &input) {
    std::ifstream file;
    openFile(file, input);
    bool is_header = false;

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        if (!is_header) {
            is_header = !is_header;
            continue;
        }
        std::stringstream ss(line);
        std::string date, pipe, value;
        ss >> date >> pipe >> value;

        if (ss.fail() || pipe != "|" || !validateDate(date)) {
            std::cout << "Error: : bad input => " << line << std::endl;
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
