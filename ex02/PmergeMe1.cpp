#include "PmergeMe.hpp"

/*----------constructor--------------*/

// PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) {
	this->vector = other.vector;
	this->deque = other.deque;
}
// PmergeMe& PmergeMe::operator=(const PmergeMe& other) {}


/*-------------METHODS---------------------*/

void PmergeMe::takeInput()
{
	for (int i = 1; input[i]; i++) {
		int j = 0;
		while (input[i][j]) {
			if (isdigit(input[i][j]) == false) {
				throw std::invalid_argument("invalid input, must be all digits and non-negative\n");
				j++;
			}
		}
		this->vector.push_back(atoi(input[i]));
		this->deque.push_back(atoi(input[i]));
	}
	// no dup check
	std::vector<int> tmp = this->vector;
	std::sort(tmp.begin(), tmp.end());
	for (size_t i = 0; i < tmp.size(); i++) {
		if (tmp[i] == tmp[i + 1]) {
			throw std::invalid_argument("duplication of number!");
		}
	}
	printBef();
}

void PmergeMe::printVec(std::vector<int>& vec)
{
	std::vector<int>::iterator it;
	for (it = vec.begin(); it != vec.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printDeq(std::deque<int>& deq)
{
	std::deque<int>::iterator it;
	for (it = deq.begin(); it != deq.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printBef()
{
	std::cout << "Before: ";
	for (int i = 1; input[i]; i++) {
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printRes()
{
	clock_t sttime;
	clock_t edtime;
	double vectm;
	double deqtm;

	sttime = clock();
	vectorSort(vector);
	edtime = clock();
	vectm = ((double) (sttime - edtime)) / CLOCKS_PER_SEC;
	printVec(vector);

	sttime = clock();
	dequeSort(deque);
	edtime = clock();
	deqtm = ((double) (sttime - edtime)) / CLOCKS_PER_SEC;
	printDeq(deque);
	
	std::cout << "Time to process a range of " << vector.size() << " elements with std::vector : " << vectm << " us\n";
	std::cout << "Time to process a range of " << vector.size() << " elements with std::deque : " << deqtm << " us\n";
}

// 0, 1, 1, 3, 5, 11, 21
// j(0) = 0; j(1) = 1; j(n) = j(n-1) + 2j(n-2) for n>=2
// std::vector<size_t> PmergeMe::calcuJacob(size_t size)
// {
// 	std::vector<size_t> jk;
// 	// edge case handle
// 	if (size == 0) {
// 		return jk; // return empty std::vector, cuz no element to insert!
// 	}
// 	jk.push_back(1); // not empty, push 1st element 
// 	if (size > 1) {
// 		jk.push_back(3); // at this point, {1, 3} in jk
// 		size_t i = 2; // the formula starts from n >= 2
// 		while (jk.back() < size) {
// 			// the insertion place is samller than the size of chain
// 			int nextJk = jk[size - 1] + (2 * jk[size - 2]);
// 			jk.push_back(nextJk);
// 			i++;
// 		}
// 	}
// 	return jk;
// }

// template <typename T>
// std::pair<std::vector<std::pair<int, int>>, std::pair<int, bool>> PmergeMe::makePair(const T& container)
// {
// 	int oddEle;
// 	std::vector<std::pair<int, int>> pairs;
// 	size_t limits = container.size();
	
// 	bool hasOddEle = container.size() % 2; // 1 => has, 0 => even
// 	if (hasOddEle == true) {
// 		oddEle = container.back();
// 		limits -= 1;
// 	} else {
// 		oddEle = 0;
// 	}
// 	for (size_t i = 0; i < limits; i += 2)
// 	{
// 		int a = container[i];
// 		int b = container[i + 1];
// 		if (a > b) {
// 			std::swap(a, b);
// 		}
// 		pairs.push_back({a, b}); // {small, big}
// 	}
// 	return {pairs, {oddEle, hasOddEle}};
// }

// static bool compareScnd(const std::pair<int, int>& a, const std::pair<int, int>& b)
// {
// 	return a.second < b.second;
// }

/** NOTE:
 * std::sort() with 3 para, 3rd is optional, if omitted, go '<' sorting
 * here mean: pair with samller .second go front
 */
// void PmergeMe::sortPair(std::vector<std::pair<int, int>>& pairs)
// {
// 	// para ' pairs' is from the 'makePair()'
// 	std::sort(pairs.begin(), pairs.end(), compareScnd);
// }


// void PmergeMe::printTime()
// {
// 	//
// }

// template <typename T>
// void PmergeMe::binaryInsert(T& container, int val, size_t size)
// {
// 	//binary insert
// 	if (size == 0) {
// 		container.insert(container.begin(), val);
// 	}
// 	size_t left_pos = 0;
// 	size_t end = size;
// 	while (left_pos < end) {
// 		size_t pos = left_pos + ((end - left_pos) / 2);
// 		if (container[pos] < val) {
// 			left_pos = pos + 1; // compare with next right (bigger) one
// 		} else {
// 			end = pos; // limit searching scope at middle pos and left
// 		}
// 	}
// 	container.insert(container.begin() + left_pos, val);
// }

/*-------------vector------------*/

void PmergeMe::vectorInsert(int st, int ed)
{
	for (int sortedIdx = st; sortedIdx < ed; ++sortedIdx) {
		int valToInsrt = vector[sortedIdx + 1];
		int insrtPos = sortedIdx + 1;
		while (insrtPos > st && vector[insrtPos - 1] > valToInsrt)
		{
			vector[insrtPos] = vector[insrtPos - 1];
			insrtPos--;
		}
		vector[insrtPos] = valToInsrt;
	}
}

void PmergeMe::vectorMerge(int st, int mid, int ed)
{
	int left = mid - st + 1;
	int right = ed - mid;

	int lIdx = 0;
	int rIdx = 0;
	std::vector<int> lPart(vector.begin() + st, vector.begin() + mid + 1);
	std::vector<int> rPart(vector.begin() + mid + 1, vector.begin() + ed + 1);
	for (int i = st; i <= ed; ++i) {
		// right-half at end, go to left
		if (rIdx == right) {
			vector[i] = lPart[lIdx];
			lIdx++;
		}
		if (lIdx == left) {
			vector[i] = rPart[rIdx];
			rIdx++;
		}
		else if (rPart[rIdx] > lPart[lIdx]) {
			vector[i] = lPart[lIdx]; // find smallest one in range
			lIdx++;
		} else {
			vector[i] = rPart[rIdx];
			rIdx++;
		}
	}
}

void PmergeMe::vectorSort(std::vector<int>& container)
{
	// if (container.size() <= 1) {
	// 	return ;
	// }

	// std::pair<std::vector<std::pair<int, int>>, std::pair<int, bool>> result = makePair(container);
	// // auto [pairs, oddInfo] = makePair(container);
	// std::vector<std::pair<int, int>> pairs = result.first;
	// std::pair<int, bool> oddInfo = result.second;
	// bool hadOdd = oddInfo.second;
	// int oddEle = oddInfo.first;

	// sortPair(pairs);

	// std::vector<int> bigChain;
	// std::vector<int> smallChain;
	// for (size_t i = 0; i < pairs.size(); ++i) {
	// 	const std::pair<int, int>& pair = pairs[i];
	// 	bigChain.push_back(pair.second);
	// 	smallChain.push_back(pair.first);
	// }
	// if (smallChain.empty() == false) {
	// 	bigChain.insert(bigChain.begin(), smallChain[0]);
	// 	smallChain.erase(smallChain.begin());
	// }
	// // form b1, a1, a2, ... an, this keep b1 and all a's in big chain
	// std::vector<size_t> jks = calcuJacob(smallChain.size()); // the size of b's decide how far we'll go in 1, 3, 5, 11...
	// std::vector<bool> inserted = std::vector<bool>(smallChain.size(), false);
	// // create a vec(bool) => [ f, f ... size...f]
	// for (size_t jkOrder : jks) {
	// 	size_t start;
	// 	if (jkOrder <= smallChain.size()) {
	// 		start = jkOrder - 1;
	// 	} else {
	// 		start = smallChain.size() - 1;
	// 	}
	// 	while (start < smallChain.size() && !inserted[start]) {
	// 		size_t instPos = start + 1; // up boundary for inserting
	// 		size_t lenthOfSearch = instPos + bigChain.size() - smallChain.size();
	// 		binaryInsert(bigChain, smallChain[start], lenthOfSearch);
	// 		inserted[start] = true; // insetred in prev step
	// 		if (start == 0) {
	// 			break ;
	// 		}
	// 		start--;
	// 	}
	// }
	// for (size_t i = 0; i < smallChain.size(); i++) {
	// 	if (inserted[i] == false) {
	// 		binaryInsert(bigChain, smallChain[i], bigChain.size());
	// 	}
	// }
	// if (hadOdd == true) {
	// 	binaryInsert(bigChain, oddEle, bigChain.size());
	// }
	// container = bigChain;
}

/*--------------deque------------*/

void PmergeMe::dequeSort(std::deque<int>& container)
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

	std::deque<int> bigChain;
	std::vector<int> smallChain;
	for (size_t i = 0; i < pairs.size(); ++i) {
		const std::pair<int, int>& pair = pairs[i];
		bigChain.push_back(pair.second);
		smallChain.push_back(pair.first);
	}
	if (smallChain.empty() == false) {
		bigChain.insert(bigChain.begin(), smallChain[0]);
		smallChain.erase(smallChain.begin());
	}
	// form b1, a1, a2, ... an, this keep b1 and all a's in big chain
	std::vector<size_t> jks = calcuJacob(smallChain.size()); // the size of b's decide how far we'll go in 1, 3, 5, 11...
	std::vector<bool> inserted = std::vector<bool>(smallChain.size(), false);
	// create a vec(bool) => [ f, f ... size...f]
	for (size_t jkOrder : jks) {
		size_t start;
		if (jkOrder <= smallChain.size()) {
			start = jkOrder - 1;
		} else {
			start = smallChain.size() - 1;
		}
		while (start < smallChain.size() && !inserted[start]) {
			size_t instPos = start + 1; // up boundary for inserting
			size_t lenthOfSearch = instPos + bigChain.size() - smallChain.size();
			binaryInsert(bigChain, smallChain[start], lenthOfSearch);
			inserted[start] = true; // insetred in prev step
			if (start == 0) {
				break ;
			}
			start--;
		}
	}
	for (size_t i = 0; i < smallChain.size(); i++) {
		if (inserted[i] == false) {
			binaryInsert(bigChain, smallChain[i], bigChain.size());
		}
	}
	if (hadOdd == true) {
		binaryInsert(bigChain, oddEle, bigChain.size());
	}
	container = bigChain;
}
