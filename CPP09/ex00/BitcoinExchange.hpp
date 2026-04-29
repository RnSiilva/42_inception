/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 23:28:37 by resilva           #+#    #+#             */
/*   Updated: 2026/04/29 22:16:08 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

class BitcoinExchange {
	private:
		std::map<std::string, float> _data; // We store the data.csv file here
		
	public:
		// OCF
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		// Main functions
		void	loadDatabase(const std::string &filename); // Read the data.csv
		void	processInput(const std::string &filename); // Read the user's input.txt file

		// Aux. functions
		bool	isValidDate(const std::string &date); //Validate YYYY-MM-DD
		bool	isValidValue(const std::string &value); // Validate 0 to 1000
		float	getExchangeRate(const std::string &date); // Search in map
		void	displayResult(const std::string &date, float amount);
};