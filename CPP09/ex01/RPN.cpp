/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 23:27:19 by resilva           #+#    #+#             */
/*   Updated: 2026/05/06 22:21:14 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// Static member initialization
std::stack<int> RPN::_stack;

// Builders and Destroyer (Private - Orthodox Canonical Form)
RPN::RPN() {}
RPN::RPN(const RPN &copy) { (void)copy; }
RPN &RPN::operator=(const RPN &other) { (void)other; return *this; }
RPN::~RPN() {}

bool RPN::isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

void RPN::executeOperation(char op) {
	if (_stack.size() < 2)
		throw std::runtime_error("Error");
	
	int b = _stack.top();
	_stack.pop();

	int a = _stack.top();
	_stack.pop();

	int result = 0;
	switch (op) {
		case '+': result = a + b; break;
		case '-': result = a - b; break;
		case '*': result = a * b; break;
		case '/':
			if (b == 0)
				throw std::runtime_error("Error");
			result = a / b; break;
	}
	_stack.push(result);
}

void RPN::calculate(const std::string &expression) {
	while (!_stack.empty())
		_stack.pop();

	std::istringstream iss(expression);
	std::string token;
	
	while (iss >> token) {
		if (token.length() == 1 && isdigit(token[0]))
			_stack.push(token[0] - '0');
		else if (token.length() == 1 && isOperator(token[0]))
			executeOperation(token[0]);
		else
			throw std::runtime_error("Error");
	}

	// In the end, there should be EXACTLY one element left in the stack.
	if (_stack.size() != 1)
		throw std::runtime_error("Error");

	std::cout << _stack.top() << std::endl;
}