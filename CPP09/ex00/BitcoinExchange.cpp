/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 23:28:39 by resilva           #+#    #+#             */
/*   Updated: 2026/04/29 22:38:18 by resilva          ###   ########.fr       */
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
	std::ifstream dbFile(filename.c_str());
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
	std::ifstream input(filename.c_str());
	if (!input.is_open())
		throw std::runtime_error("Error: could not open file.");
	std::string	line;
	std::getline(input, line); // skip header
	while (getline(input, line)) {
		if (line.empty()) continue;
		size_t pipe = line.find('|');
		if (pipe == std::string::npos) {
			std::string msg = "Error: bad input => " + line + ".";	
			throw std::runtime_error(msg);
		}
		
		// Separa data e valor, removendo espaços em branco
		std::string	date = line.substr(0, pipe);
		date.erase(date.find_last_not_of(" \t") + 1); // trim right
		std::string	valueStr = line.substr(pipe + 1);

		if (!isValidDate(date)) {
			std::string msg = "Error: bad input => " + date + ".";
			throw std::runtime_error(msg);
		}

		// Validação do valor
		if (!isValidValue(valueStr)) {
			continue;
		}
		
		float val = static_cast<float>(atof(valueStr.c_str()));
		displayResult(date, val);
	}
	
}

bool	BitcoinExchange::isValidDate(const std::string &date)
{
	
}

bool	BitcoinExchange::isValidValue(const std::string &valueStr)
{
	char	*endPtr;
	float	val = std::strtof(valueStr.c_str(), &endPtr);

	// 1. Verifica se a string não está vazia ou se contém apenas espaços
	if (valueStr.find_first_not_of(" \t") == std::string::npos) {
		std::cerr << "Error: empty value." << std::endl;
		return false;
	}

	// 2. Verifica se havia lixo após o número (ex: "1.2abc")
	if (*endPtr != '\0' && !isspace(*endPtr)) {
		std::cerr << "Error: bad input => " << valueStr << std::endl;
		return false;
	}

	// 3. Regra: Valor deve ser positivo
	if (val < 0) {
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	
	// 4. Regra: Valor entre 0 e 1000
	if (val > 1000) {
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}

	return true;

}

float	BitcoinExchange::getExchangeRate(const std::string &date)
{
	
}

void	BitcoinExchange::displayResult(const std::string &date, float amount) {
	//Busca a data exata ou o primeiro elemento que nao seha menor que 'date'
	std::map<std::string, float>::iterator it = _data.lower_bound(date);
	
	if (it != _data.end() && it->first == date) {
		// Encontrou a data exata
		std::cout << date << " => " << amount << " = " << amount * it->second << std::endl;
	} else {
		// Se it for o início e não for igual, não existe data anterior
		if (it == _data.begin()) {
			std::cerr << "Error: no exchange rate found for " << date << std::endl;
		} else {
			// Volta um para pegar a data anterior mais próxima
			--it;
			std::cout << date << " => " << amount << " = " << amount * it->second << std::endl;
		}
	}
}
