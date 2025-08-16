/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:48:02 by ewu               #+#    #+#             */
/*   Updated: 2025/08/16 16:53:04 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <chrono>
#include <climits>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>


/**
 * CONTAINER:
 * vector, deque
 * FUNCTION:
 * createPair(); sortPaor();
 * bigChain();
 * smallCh();
 * 	insert samllch() to bigChain() using Jacobthals number, binary search
 * QUESTION: why jacob number??
 * binary插入时，对于长度k的array，最多需要lgk次比较（k=8，lg8=3；k=32，lgk=5）
 * j(0) = 0; j(1) = 1; j(n) = j(n-1) + 2j(n-2) for n>1
 *
 * 
 */
class PmergeMe
{
private:
	std::vector<int> vector;
	std::deque<int> deque;
	
	// int size: the size of 'pending-chain, according to the num of element in the chain to cal the kacob order
	std::vector<int> calcuJacob(size_t size); //for nbr > 1
	
	// the general pairing
	template <typename T>
	std::pair<std::vector<std::pair<int, int>>, std::pair<int, bool>> makePair(const T& container);
	void sortPair(std::vector<std::pair<int, int>>& pairs);
	bool compareScnd(const std::pair<int, int>& a, const std::pair<int, int>& b);
		
	// vector sorting
	void 
	
	
	// deque sorting
	
	
	
public:

	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);

	
	// print the msg
	void printNum();
	void printTime();

};



#endif
// struct pairInfo
	// {
	// 	std::vector<std::pair<int, int> > pairs;
	// 	bool isOdd = false;
	// 	int oddNbr = 0;
	// 	pairInfo(std::vector<std::pair<int, int> > p, bool odds, int oddsize) : pairs(p), isOdd(odds), oddNbr(oddsize) {}
	// };
	
	// template <typename T>
	// pairInfo makePair(const T& container);