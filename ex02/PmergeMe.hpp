/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:48:02 by ewu               #+#    #+#             */
/*   Updated: 2025/08/19 21:18:31 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <ostream>
#include <iostream>
#include <sstream>
#include <ctime>
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
	
public:	
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();
	
	// call vector sort process
	void callVectSort(char** av);
	
	// print the msg
	void printVec_b();
	void printVec_a();
	void printDeq_b(std::deque<int>& deq);
	void printBef();
	// void noDup(); in printbef() now, may remove
	void printRes();
	
private:

// vector sort
	std::vector<int> vector;
	std::vector<int> insrtPos;
	std::vector<std::pair<int, int>> vecPair;
	std::vector<int> bigChain;
	std::vector<int> smallChain;
	std::vector<int> jkOrder;
	
	void takeIputVec(char** av);
	void makeVecPair();
	void sortVecPair();
	void splitVecSort(std::vector<std::pair<int, int>>& arr, int st, int ed);
	void mergeVec(std::vector<std::pair<int, int>>& arr, int st, int mid, int ed);
	void makeChain();
	int binSrchVec(std::vector<int> arr, int target, int st, int ed);
	int calcuJknbr(int size);
	void createJkOrder();
	void createInsrtOrder();
	void insertion();
	
	
	std::deque<int> deque;

	// int size: the size of 'pending-chain, according to the num of element in the chain to cal the kacob order
	
	// the general pairing
	// template <typename T>
	// std::pair<std::vector<std::pair<int, int>>, std::pair<int, bool>> makePair(const T& container);
	// void sortPair(std::vector<std::pair<int, int>>& pairs);
	//bool compareScnd(const std::pair<int, int>& a, const std::pair<int, int>& b);
	
	// template <typename T>
	// void binaryInsert(T& container, int val, size_t size);
		
	
	// deque sorting
	// void deqInsert(int st, int ed);
	// void depMerge(int st, int mid, int ed);
	// void dequeSort(std::deque<int>& container);


};




/* template class:
 'typename T' as pare
 template<typename, typename> class container: is container template
 like: pmergeme<int, vector> sortVec;
*/

// template <typename T, template <typename, typename> class Container>
// class PmergeMe
// {
// 	PmergeMe<T, Container>();
// 	PmergeMe<T, Container>(const PmergeMe<T, Container>& other);
// 	~PmergeMe<T, Container>();
// 	PmergeMe<T, Container>& operator=(const PmergeMe<T, Container>& other);
	
// 	// containertype: type alias (using = typedef)
// 	using ContainerType = Container<T, std::allocator<T>>;
// 	ContainerType sorting(const ContainerType& arr) const;
// 	ContainerType merging(ContainerType t1, ContainerType t2) const;
// };

 
	



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