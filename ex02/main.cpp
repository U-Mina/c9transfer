/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:59:38 by ewu               #+#    #+#             */
/*   Updated: 2025/08/17 19:50:41 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char** av)
{
	if (ac < 2)
	{
		throw std::invalid_argument("Invalid argument number!");
	}
	try
	{
		PmergeMe p;
		p.takeInput(ac, av);
		p.printRes();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}