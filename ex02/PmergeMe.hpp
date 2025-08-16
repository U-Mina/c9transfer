/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:48:02 by ewu               #+#    #+#             */
/*   Updated: 2025/08/16 11:20:52 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>
#include <ctime>
#include <climits>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>


/**
 * FUNCTION:
 * createPair(); sortPaor();
 * bigChain();
 * smallCh(); => insert to bigChain() using Jacobthals number, binary search
 * QUESTION: why jacob number??
 * 
 */
class PmergeMe
{
	
public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe& copy);
	PmergeMe& operator=(const PmergeMe& other);
	

};



#endif