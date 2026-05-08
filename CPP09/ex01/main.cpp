/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 23:27:40 by resilva           #+#    #+#             */
/*   Updated: 2026/05/06 02:03:27 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Usage: ./RPN \"expression\"" << std::endl;
		return (EXIT_FAILURE);
	}
	
	try {
		RPN::calculate(av[1]);
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}