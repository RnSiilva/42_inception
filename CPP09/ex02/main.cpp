/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 20:58:27 by resilva           #+#    #+#             */
/*   Updated: 2026/05/08 05:26:17 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static bool validInput(int ac, char **av, std::vector<int> &vec, std::deque<int> &deq) {
	for (int i = 1; i < ac; ++i) {
		char *end;
		long val = std::strtol(av[i], &end, 10);
		if (*end != '\0' || val < 0 || val > 2147483647)
			return false;
		
		vec.push_back(static_cast<int>(val));
		deq.push_back(static_cast<int>(val));
	}
	return true;
}

int main(int ac, char **av) {
	if (ac < 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	std::vector<int> vec;
	std::deque<int> deq;
	if (!validInput(ac, av, vec, deq))
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	PmergeMe::run(vec, deq);
}