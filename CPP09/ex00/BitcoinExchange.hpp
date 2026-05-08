/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 23:28:37 by resilva           #+#    #+#             */
/*   Updated: 2026/04/30 02:36:59 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>

class BitcoinExchange {
	private:
		std::map<std::string, float> _data; // We store the data.csv file here
		
	public:
		// OCF
		BitcoinExchange(const std::string &dbFile);
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		// Main functions
		void	loadDatabase(const std::string &filename); // Read the data.csv
		void	processInput(const std::string &filename); // Read the user's input.txt file

		// Aux. functions
		bool	isValidDate(const std::string &date); //Validate YYYY-MM-DD
		bool	isValidValue(const std::string &value); // Validate 0 to 1000
		void	displayResult(const std::string &date, float amount); // Search in map and display the result
};