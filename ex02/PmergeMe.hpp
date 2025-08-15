/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:48:02 by ewu               #+#    #+#             */
/*   Updated: 2025/08/15 20:46:12 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

class PmergeMe
{
private:
	std::vector<int> _vector;
	std::deque<int> _deque;

	// create jacobsthal number order for insertion
	static std::vector<size_t> _calJacob(size_t n);
	
	// main algorithm, create main_chain and pending_chain, 
	// insert P to M with Jacob order with binary search
	void _vectorSort(int _begin, int _end);
	void _dequeSort(int _begin, int _end);

	// utilities
	void _insertVec(int _begin, int _end);
	void _insertDeque(int _begin, int _end);
	bool _vecDup();
	bool _dequeDup();
	
public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe& copy);
	PmergeMe& operator=(const PmergeMe& other);
	

};



#endif