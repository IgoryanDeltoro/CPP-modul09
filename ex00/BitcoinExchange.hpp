#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <exception>
#include <algorithm> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <map>

class BitcoinExchange {
    private:
        std::map<std::string, double> _database;

        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);

    public:
        BitcoinExchange();
        ~BitcoinExchange();

        void findBtcRate(const std::string &input);
        void getDataFromDB(const std::string &input);

};

#endif 