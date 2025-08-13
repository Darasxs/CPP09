/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:18:18 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/08/13 17:13:23 by dpaluszk         ###   ########.fr       */
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
	while(getline(databaseInstance, line))
	{
		std::istringstream stream(line);
		std::string date, exchangeRate;
		
		getline(stream, date, ',');
		getline(stream, exchangeRate);
		
		//std::cout << line;
		//std::cout << std::endl;
	}

	databaseInstance.close();
}
