/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 23:28:39 by resilva           #+#    #+#             */
/*   Updated: 2026/05/05 23:14:22 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &dbFile) {
	loadDatabase(dbFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : _data(copy._data){}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_data = other._data;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// Loads the database into the map
void	BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream dbFile(filename.c_str());
	if (!dbFile.is_open())
		throw std::runtime_error("could not open database file.");
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
// Processes the input file, validates, and outputs results
void	BitcoinExchange::processInput(const std::string &filename)
{
	std::ifstream input(filename.c_str());
	
	if (!input.is_open())
		throw std::runtime_error("could not open file.");

	std::string	line;
	std::getline(input, line); // skip header
	if (line != "date | value")
		throw std::runtime_error("invalid fields in " + filename);

	while (getline(input, line)) {
		if (line.empty()) {
			std::cerr << "Error: bad input => (empty line)" << std::endl;
			continue;
		}
		size_t pipe = line.find('|');
		if (pipe == std::string::npos) {	
			std::cerr << "Error: bad input => " + line << std::endl;
			continue;
		}
		
		// Separates data and values ​​by removing whitespace.
		std::string	date = line.substr(0, pipe);
		date.erase(0, date.find_first_not_of(" \t"));
		date.erase(date.find_last_not_of(" \t") + 1);
		
		std::string	valueStr = line.substr(pipe + 1);
		valueStr.erase(0, valueStr.find_first_not_of(" \t"));
		valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

		// Date validation
		if (!isValidDate(date)) {
			std::cerr << "Error: bad input => " + date << std::endl;
			continue;
		}
		// Value validation
		if (!isValidValue(valueStr)) {
			continue;
		}
		
		float val = static_cast<float>(atof(valueStr.c_str()));
		displayResult(date, val);
	}
	input.close();
}

bool	BitcoinExchange::isValidDate(const std::string &date)
{
	// 1. Basic format validation: YYYY-MM-DD (10 characters)
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	// 2. Integer extraction
	int	year, month, day;
	std::istringstream ssYear(date.substr(0, 4));
	std::istringstream ssMonth(date.substr(5, 2));
	std::istringstream ssDay(date.substr(8, 2));

	if (!(ssYear >> year) || !(ssMonth >> month) || !(ssDay >> day))
		return false;
	
	// 3. Year/Month/Day Validation
	if (year < 0 || month < 1 || month > 12 || day < 1)
		return false;
	int	daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	// 4. Adjustment for Leap Year
	if (month == 2) {
		bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
		if (day > (isLeap ? 29 : 28))
			return false;
	} else if (day > daysInMonth[month - 1]) {
		return false;
	}

	return true;
}

bool	BitcoinExchange::isValidValue(const std::string &valueStr)
{
	char	*endPtr;
	float	val = strtof(valueStr.c_str(), &endPtr);

	// 1. Checks if the string is not empty or if it contains only spaces.
	if (valueStr.find_first_not_of(" \t") == std::string::npos) {
		std::cerr << "Error: empty value." << std::endl;
		return false;
	}

	// 2. Check if there is garbage after the number (e.g., "1.2abc")
	if (*endPtr != '\0' && !isspace(*endPtr)) {
		std::cerr << "Error: bad input => " << valueStr << std::endl;
		return false;
	}

	// 3. Rule: The value must be positive.
	if (val < 0) {
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	
	// 4. Rule: Value between 0 and 1000
	if (val > 1000) {
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}

	return true;
}

void	BitcoinExchange::displayResult(const std::string &date, float amount) {
	// Find the exact date or the first element that is not earlier than 'date'.
	std::map<std::string, float>::iterator it = _data.lower_bound(date);
	
	if (it != _data.end() && it->first == date) {
		// Found the exact date
		std::cout << date << " => " << amount << " = " << amount * it->second << std::endl;
	} else {
		// If 'it' is the beginning and is not equal, there is no previous date.
		if (it == _data.begin()) {
			std::cerr << "Error: no exchange rate found for " << date << std::endl;
		} else {
			// Go back one to get the nearest previous date.
			--it;
			std::cout << date << " => " << amount << " = " << amount * it->second << std::endl;
		}
	}
}
