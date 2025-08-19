/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:18:18 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/08/19 19:26:25 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{

}

BitcoinExchange::BitcoinExchange(const std::string &databaseFile)
{
	openDatabaseFile(databaseFile);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &copy)
{
	*this = copy;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &copy)
{
	if (this != &copy)
	{
		//
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange(void)
{
}
void BitcoinExchange::openDatabaseFile(const std::string &databaseFile)
{
	std::ifstream databaseInstance(databaseFile);

	if(!databaseInstance.is_open())
	{
		std::cerr << "Error while opening the database file." << std::endl;
		return ;
	}

	std::string line;
	if(getline(databaseInstance, line) && line != "date,exchange_rate")
	{
		std::cout << "Error: wrong header in the database file!" << std::endl;
		return ;
	}
	while(getline(databaseInstance, line))
	{
		// do the parsing for the date if it is valid YYYY-MM-DD
		// check if length of the date is exactly 10, if '-' is at position 4 and 7
		// check if the date year month and day are valid integers
		// check if the exchange_rate is a valid floating point number
		// add "date and exchange_rate" into the map
		// convert exchange_rate to a floating point from a string before storing it

		std::istringstream stream(line);
		std::string date, exchangeRate;
		getline(stream, date, ',');
		getline(stream, exchangeRate);

		//std::cout << line;
		//std::cout << std::endl;
		if(parseDate(date) && parseExchangeRate(exchangeRate))
		{
			// function to insert date into a map
		}
		else
		{
			std::cerr << "Error: invalid data in the following line: " << line << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}

	databaseInstance.close();
}
