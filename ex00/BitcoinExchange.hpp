#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdlib>
#include <exception>

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

std::ostream& operator<<(std::ostream &os, BitcoinExchange &btc);

#endif 