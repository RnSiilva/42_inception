/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 23:26:11 by resilva           #+#    #+#             */
/*   Updated: 2026/05/06 21:36:00 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstdlib>

class RPN {
	private:
		static std::stack<int>	_stack;

		// Private constructors to avoid instantiation (utility class)
		RPN();
		RPN(const RPN &copy);
		RPN &operator=(const RPN &other);
		~RPN();

		// Internal auxiliary functions
		static bool isOperator(char c);
		static void	executeOperation(char op);
		
	public:
		// The main function that is called in the main method.
		static void calculate(const std::string &expression);
};