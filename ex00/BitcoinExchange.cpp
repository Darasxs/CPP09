/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:18:18 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/08/24 17:37:53 by dpaluszk         ###   ########.fr       */
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

bool BitcoinExchange::parseDate(const std::string &date)
{
	if(date.length() != 10 || date[4] != '-' || date[7] != '-')
	{
		std::cout << "5" << std::endl;
		return false;
	}

	int year, month, day;
	try
	{
		year = std::stoi(date.substr(0, 4));
		month = std::stoi(date.substr(5, 2));
		day = std::stoi(date.substr(8, 2));
	}
	catch (const std::exception &e)
	{
		std::cout << "4" << std::endl;
		return false;
	}

	if (year <= 0 || month < 1 || month > 12 || day < 1)
	{
		std::cout << "3" << std::endl;
		return false;
	}

	const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

	if (month == 2 && isLeapYear)
	{
		if (day > 29)
		{
			std::cout << "1" << std::endl;
			return false;
		}
	}
	else
	{
		if(day > daysInMonth[month])
		{
			std::cout << "2" << std::endl;
			return false;
		}
	}

	return true;
}

bool BitcoinExchange::parseExchangeRate(const std::string &exchangeRate)
{
	try
	{
		double exchangeRateDouble = std::stod(exchangeRate);
		if (exchangeRateDouble < 0)
		{
			std::cout << "6" << std::endl;
			return false;
		}
		if (exchangeRateDouble > INT_MAX)
		{
			std::cout << "7" << std::endl;
			return false;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: invalid exchange rate format: " << exchangeRate << std::endl;
		return false;
	}
	return true;
}

void BitcoinExchange::updateMap(const std::string &date, float exchangeRate)
{
	database[date] = exchangeRate;
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

		std::istringstream stream(line);
		std::string date, exchangeRate;
		getline(stream, date, ',');
		getline(stream, exchangeRate);

		//std::cout << line;
		//std::cout << std::endl;
		if (parseDate(date) && parseExchangeRate(exchangeRate))
		{
			updateMap(date, std::stof(exchangeRate));
		}
		else
		{
			std::cerr << "Error: invalid data in the following line: " << line << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
	databaseInstance.close();
}
