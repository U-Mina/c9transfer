#include "PmergeMe.hpp"

/*----------constructor--------------*/

// PmergeMe::PmergeMe() {}
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
	}
	return jk;
}

template <typename T>
std::pair<std::vector<std::pair<int, int>>, std::pair<int, bool>> PmergeMe::makePair(const T& container)
{
	int oddEle;
	std::vector<std::pair<int, int>> pairs;
	size_t limits = container.size();
	
	bool hasOddEle = container.size() % 2; // 1 => has, 0 => even
	if (hasOddEle == true) {
		oddEle = container.back();
		limits -= 1;
	} else {
		oddEle = 0;
	}
	for (size_t i = 0; i < limits; i += 2)
	{
		int a = container[i];
		int b = container[i + 1];
		if (a > b) {
			std::swap(a, b);
		}
		pairs.push_back({a, b}); // {small, big}
	}
	return ({pairs, {oddEle, hasOddEle}});
}

bool PmergeMe::compareScnd(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
	return a.second < b.second;
}

/** NOTE:
 * std::sort() with 3 para, 3rd is optional, if omitted, go '<' sorting
 * here mean: pair with samller .second go front
 */
void PmergeMe::sortPair(std::vector<std::pair<int, int>>& pairs)
{
	// para ' pairs' is from the 'makePair()'
	std::sort(pairs.begin(), pairs.end(), compareScnd);
}

void PmergeMe::printNum()
{
	//
}

void PmergeMe::printTime()
{
	//
}

/*-------------vector------------*/

void PmergeMe::vectorSort(std::vector<int>& container)
{
	if (container.size() <= 1) {
		return ;
	}
	std::pair<std::vector<std::pair<int, int>>, std::pair<int, bool>> result = makePair(container);
	// auto [pairs, oddInfo] = makePair(container);
	std::vector<std::pair<int, int>> pairs = result.first;
	std::pair<int, bool> oddInfo = result.second;
	bool hadOdd = oddInfo.second;
	int oddEle = oddInfo.first;

	sortPair(pairs);

	std::vector<int> bigChain;
	std::vector<int> smallChain;
	for (size_t i = 0; i < pairs.size(); ++i) {
		const std::pair<int, int>& pair = pairs[i];
		bigChain.push_back(pair.second);
		smallChain.push_back(pair.first);
		//
	}
}

/*--------------deque------------*/
