/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   */
/*   Created: 2025/08/02 15:18:18 by dpaluszk          #+#    #+#             */
/*   Updated: 2026/01/06 21:48:16 by dpaluszk         ###   ########.fr       */
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
		this->database = copy.database;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange(void)
{
}

bool BitcoinExchange::parseDate(const std::string &date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
	{
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
		return false;
	}

	if (year <= 0 || month < 1 || month > 12 || day < 1)
	{
		return false;
	}

	const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

	if (month == 2 && isLeapYear)
	{
		if (day > 29)
		{
			return false;
		}
	}
	else
	{
		if (day > daysInMonth[month])
		{
			return false;
		}
	}

	return true;
}

bool BitcoinExchange::parseExchangeRate(const std::string &exchangeRate)
{
	try
	{
		size_t pos = 0;
		double exchangeRateDouble = std::stod(exchangeRate, &pos);
		if (exchangeRateDouble < 0 || pos != exchangeRate.length())
		{
			return false;
		}
		if (exchangeRateDouble > INT_MAX)
		{
			return false;
		}
	}
	catch (const std::exception &e)
	{
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
	if (databaseFile != "data.csv")
	{
		std::cerr << "Error: Only 'data.csv' is allowed to populate the database." << std::endl;
		return;
	}

	std::ifstream databaseInstance(databaseFile);

	if (!databaseInstance.is_open())
	{
		std::cerr << "Error while opening the database file." << std::endl;
		return;
	}

	std::string line;
	if (getline(databaseInstance, line) && line != "date,exchange_rate")
	{
		std::cerr << "Error: invalid header in the database file!" << std::endl;
		return;
	}

	while (getline(databaseInstance, line))
	{
		std::istringstream stream(line);
		std::string date, exchangeRate;
		getline(stream, date, ',');
		getline(stream, exchangeRate);

		if (parseDate(date) && parseExchangeRate(exchangeRate))
		{
			updateMap(date, std::stod(exchangeRate));
		}
		else
		{
			std::cerr << "Warning: skipping invalid data in line: " << line << std::endl;
		}
	}
	databaseInstance.close();
}

void BitcoinExchange::processInputFile(const std::string &inputFile)
{
	std::ifstream inputInstance(inputFile);

	if (!inputInstance.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	bool isFirstLine = true;
	while (getline(inputInstance, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		std::istringstream stream(line);
		std::string date, value;
		getline(stream, date, '|');
		getline(stream, value);

		date.erase(0, date.find_first_not_of(" \t"));
		date.erase(date.find_last_not_of(" \t") + 1);
		value.erase(0, value.find_first_not_of(" \t"));
		value.erase(value.find_last_not_of(" \t") + 1);

		if (!parseDate(date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		auto it = database.lower_bound(date);
		if (it == database.begin() && (it == database.end() || it->first != date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (it == database.end() || it->first != date)
		{
			--it;
		}

		try
		{
			size_t pos = 0;
			double inputValue = std::stod(value, &pos);
			if (pos != value.length())
			{
				std::cerr << "Error: bad input => " << line << std::endl;
				continue;
			}
			if (inputValue < 0)
			{
				std::cerr << "Error: not a positive number." << std::endl;
				continue;
			}
			if (inputValue > INT_MAX)
			{
				std::cerr << "Error: too large a number." << std::endl;
				continue;
			}
			std::cout << date << " => " << inputValue << " = " << inputValue * it->second << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
		}
	}
	inputInstance.close();
}
