#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <climits>

class BitcoinExchange
{
	private:
		std::map<std::string, float> database;
		void openDatabaseFile(const std::string &databaseFile);
		bool parseDate(const std::string &date);
		bool parseExchangeRate(const std::string &exchangeRate);
		void updateMap(const std::string &date, float exchangeRate);

	public:
		BitcoinExchange(void);
		BitcoinExchange(const std::string &databaseFile);
		BitcoinExchange(BitcoinExchange const &copy);
		BitcoinExchange &operator=(BitcoinExchange const &copy);
		~BitcoinExchange(void);

		void processInputFile(const std::string &inputFile);
};

#endif