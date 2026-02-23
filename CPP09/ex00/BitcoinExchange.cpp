/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 23:28:39 by resilva           #+#    #+#             */
/*   Updated: 2026/02/23 21:50:11 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : _data(copy._data){}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_data = other._data;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}


void	BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream dbFile(filename);
	if (!dbFile.is_open())
		throw std::runtime_error("Error: could not open database file.");
	std::string line;
	getline(dbFile, line); // skip header
	while (getline(dbFile, line)) {
		std::istringstream ss(line);
		std::string date, valueStr;
		if (getline(ss, date, ',') && getline(ss, valueStr)) {
			float value = static_cast<float>(atof(valueStr.c_str()));
			this->_data[date] = value;
		}
	}
	dbFile.close();
}

void	BitcoinExchange::processInput(const std::string &filename)
{
	
}

bool	BitcoinExchange::isValidDate(const std::string &date)
{
	
}

bool	BitcoinExchange::isValidValue(float value)
{
	
}

float	BitcoinExchange::getExchangeRate(const std::string &date)
{
	
}
