#include <iostream>
#include "BitcoinExchange.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Error: Enter => ./btc inputFile\n";
        return 1;
    }
    try
    {

        BitcoinExchange btc;
        
        btc.getDataFromDB("data.csv");
        btc.findBtcRate(static_cast<std::string>(av[1]));

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}