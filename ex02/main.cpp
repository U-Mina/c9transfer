/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:59:38 by ewu               #+#    #+#             */
/*   Updated: 2025/08/19 22:13:48 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char** av)
{
	PmergeMe vecP;
	if (ac == 1)
	{
		std::cerr << "Bad input!\n";
		return 1;
	}
	try
	{
		vecP.callVectSort(av);
		vecP.printVec_b();
		vecP.printVec_a();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}