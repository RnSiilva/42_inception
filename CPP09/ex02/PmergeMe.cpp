/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 18:16:11 by resilva           #+#    #+#             */
/*   Updated: 2026/05/08 14:54:28 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {};
PmergeMe::PmergeMe(const PmergeMe &copy) { (void)copy; };
PmergeMe &PmergeMe::operator=(const PmergeMe &other) { (void)other; return *this; }
PmergeMe::~PmergeMe() {};

std::vector<int> PmergeMe::generateJacobsthal(int n)
{
	std::vector<int> jacob;
	jacob.push_back(0);
	jacob.push_back(1);

	// Formula: J(n) = J(n-1) + 2 * J(n-2)
	while (jacob[jacob.size() - 1] < n) {
		size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
		jacob.push_back(next);
	}
	return jacob;
}

std::vector<int> PmergeMe::generateInsertionOrder(int n)
{
	std::vector<int> order;
	if (n <= 0)
		return order;
	std::vector<int> jacobsthal = generateJacobsthal(n);
	int numberToPush = jacobsthal.back();
	jacobsthal.pop_back();
	while (numberToPush > jacobsthal.back()) {
		order.push_back(numberToPush);
		numberToPush--;
	}
	return order;
}

void PmergeMe::sortVector(std::vector<int> &v) {
	if (v.size() <= 1)
		return;
	if (v.size() <= 2)
	{
		if (v[0] > v[1])
			std::swap(v[0], v[1]);
		return ;
	}

	int straggler = -1;
	bool hasStraggler = false;
	if (v.size() % 2 != 0) {
		straggler = v.back();
		v.pop_back();
		hasStraggler = true;
	}

	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i < v.size(); i += 2) {
		int a = v[i], b = v[i + 1];
		pairs.push_back(std::make_pair(a > b ? a : b, a > b? b : a));
	}
	
	std::vector<int> winners, pend;
	for (size_t i = 0; i < pairs.size(); ++i) {
		winners.push_back(pairs[i].first);
		pend.push_back(pairs[i].second);
	}

	sortVector(winners);

	if (hasStraggler)
		pend.push_back(straggler);
	
	std::vector<int> mainChain = winners;
	// for (size_t i = 0; i < winners.size(); ++i)
	// 	mainChain.push_back(winners[i]);
	if (!pend.empty()) {
		std::vector<int> jacobOrder = generateInsertionOrder((int)pend.size());
		
		std::vector<bool> inserted(pend.size(), false);
		
		for (size_t k = 0; k < jacobOrder.size(); ++k) {
			int idx = jacobOrder[k];
			if (idx < (int)pend.size() && !inserted[idx]) {
				//lower_bound ou upper_bound?????
				std::vector<int>::iterator it = upper_bound(mainChain.begin(), mainChain.end(), pend[idx]);
				mainChain.insert(it, pend[idx]);
				inserted[idx] = true;
			}
		}
		for (int i = pend.size() - 1; i >= 0; --i) {
			if (!inserted[i]) {
				std::vector<int>::iterator it = upper_bound(mainChain.begin(), mainChain.end(), pend[i]);
				mainChain.insert(it, pend[i]);
			}
		}
	}
	
	v = mainChain;
}

void PmergeMe::sortDeque(std::deque<int> &dq) {
	if (dq.size() <= 1)
		return;
	if (dq.size() <= 2)
	{
		if (dq[0] > dq[1])
			std::swap(dq[0], dq[1]);
		return ;
	}

	int straggler = -1;
	bool hasStraggler = false;
	if (dq.size() % 2 != 0) {
		straggler = dq.back();
		dq.pop_back();
		hasStraggler = true;
	}

	std::deque<std::pair<int, int> > pairs;
	for (size_t i = 0; i < dq.size(); i += 2) {
		int a = dq[i], b = dq[i + 1];
		pairs.push_back(std::make_pair(a > b ? a : b, a > b? b : a));
	}
	
	std::deque<int> winners, pend;
	for (size_t i = 0; i < pairs.size(); ++i) {
		winners.push_back(pairs[i].first);
		pend.push_back(pairs[i].second);
	}

	sortDeque(winners);

	if (hasStraggler)
		pend.push_back(straggler);
	
	std::deque<int> mainChain = winners;
	// for (size_t i = 0; i < winners.size(); ++i)
	// 	mainChain.push_back(winners[i]);
	if (!pend.empty()) {
		std::vector<int> jacobOrder = generateInsertionOrder((int)pend.size());
		
		std::vector<bool> inserted(pend.size(), false);
		
		for (size_t k = 0; k < jacobOrder.size(); ++k) {
			int idx = jacobOrder[k];
			if (idx < (int)pend.size() && !inserted[idx]) {
				std::deque<int>::iterator it = upper_bound(mainChain.begin(), mainChain.end(), pend[idx]);
				mainChain.insert(it, pend[idx]);
				inserted[idx] = true;
			}
		}
		for (int i = pend.size() - 1; i >= 0; --i) {
			if (!inserted[i]) {
				std::deque<int>::iterator it = upper_bound(mainChain.begin(), mainChain.end(), pend[i]);
				mainChain.insert(it, pend[i]);
			}
		}
	}
	
	dq = mainChain;
}

void PmergeMe::displayBefore(std::vector<int> &vec) {
	std::cout << "Before: ";
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec.at(i) << " ";
	std::cout << std::endl;
}

void PmergeMe::displayAfter(std::vector<int> &vec) {
	std::cout << "After: ";
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec.at(i) << " ";
	std::cout << std::endl;
}

void PmergeMe::run(std::vector<int> &vec, std::deque<int> &deq) {
	displayBefore(vec);

	// Sorting and Measuring: Vector
	clock_t startVec = clock();
	sortVector(vec);
	clock_t endVec = clock();
	double vecTime = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1e6;

	// Sorting and Measuring: Deque
	clock_t startDeq = clock();
	sortDeque(deq);
	clock_t endDeq = clock();
	double deqTime = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1e6;

	displayAfter(vec);

	// View Times
	std::cout << "Time to process a range of " << vec.size()
			<< " elements with std::vector : " << vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << deq.size()
			<< " elements with std::deque : " << deqTime << " us" << std::endl;
}