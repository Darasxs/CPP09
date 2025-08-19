/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:18:18 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/08/19 19:18:44 by dpaluszk         ###   ########.fr       */
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

	if (!databaseInstance.is_open())
	{
		std::cerr << "Error while opening the database file." << std::endl;
		return;
	}

	std::string line;
	if (getline(databaseInstance, line) && line != "date,exchange_rate")
	{
		std::cout << "Error: wrong header in the database file!" << std::endl;
		return;
	}

	while (getline(databaseInstance, line))
	{
		std::istringstream stream(line);
		std::string date, exchangeRate;
		getline(stream, date, ',');
		getline(stream, exchangeRate);

		if (validateAndParseDate(date) && validateAndParseExchangeRate(exchangeRate))
		{
			insertDataIntoMap(date, std::stof(exchangeRate));
		}
		else
		{
			std::cerr << "Error: invalid data in line: " << line << std::endl;
		}
	}

	databaseInstance.close();
}

bool BitcoinExchange::validateAndParseDate(const std::string &date)
{
	// Check if length is 10 and '-' is at positions 4 and 7
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	// Extract year, month, and day
	int year = std::stoi(date.substr(0, 4));
	int month = std::stoi(date.substr(5, 2));
	int day = std::stoi(date.substr(8, 2));

	// Validate year, month, and day
	if (month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	// Additional checks for days in specific months and leap years can be added here
	return true;
}

bool BitcoinExchange::validateAndParseExchangeRate(const std::string &exchangeRate)
{
	try
	{
		float rate = std::stof(exchangeRate);
		if (rate < 0) // Ensure the rate is non-negative
			return false;
	}
	catch (const std::exception &e)
	{
		return false;
	}
	return true;
}

void BitcoinExchange::insertDataIntoMap(const std::string &date, float exchangeRate)
{
	// Add the date and exchange rate to the map
	dataMap[date] = exchangeRate;
}
