/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:57:01 by resilva           #+#    #+#             */
/*   Updated: 2026/05/08 05:39:25 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <ctime>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

class PmergeMe {
	private:
		PmergeMe();
		PmergeMe(const PmergeMe &copy);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		static void	sortVector(std::vector<int> &v);
		static void	sortDeque(std::deque<int> &d);

		// --- Utils ---
		static std::vector<int>	generateInsertionOrder(int n);
		static std::vector<int>	generateJacobsthal(int n);
		
		static void	displayBefore(std::vector<int> &vec);
		static void	displayAfter(std::vector<int> &vec);

	public:
		static void	run(std::vector<int> &vec, std::deque<int> &deq);
};

#endif