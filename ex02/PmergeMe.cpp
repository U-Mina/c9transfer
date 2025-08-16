#include "PmergeMe.hpp"

/*----------constructor--------------*/
PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) {}
PmergeMe& PmergeMe::operator=(const PmergeMe& other) {}

/*-------------methods---------------*/

// 0, 1, 1, 3, 5, 11, 21
// j(0) = 0; j(1) = 1; j(n) = j(n-1) + 2j(n-2) for n>=2
std::vector<int> PmergeMe::calcuJacob(size_t size)
{
	std::vector<int> jk;

	// edge case handle
	if (size == 0) {
		return jk; // return empty std::vector, cuz no element to insert!
	}
	jk.push_back(1); // not empty, push 1st element 
	if (size > 1) {
		jk.push_back(3); // at this point, {1, 3} in jk
		size_t i = 2; // the formula starts from n >= 2
		while (jk.back() < size) {
			// the insertion place is samller than the size of chain
			int nextJk = jk[size - 1] + (2 * jk[size - 2]);
			jk.push_back(nextJk);
			i++;
		}
		return jk;
	}

}
