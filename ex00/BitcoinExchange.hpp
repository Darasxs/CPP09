#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

class BitcoinExchange
{
	private:
		void openDatabaseFile(const std::string &databaseFile);
		std::map<std::string, float> database;

	public:
		BitcoinExchange(void);
		BitcoinExchange(const std::string &databaseFile);
		BitcoinExchange(BitcoinExchange const &copy);
		BitcoinExchange &operator=(BitcoinExchange const &copy);
		~BitcoinExchange(void);

		//void execute(const std::string &inputFile);
};

#endif