#include "PmergeMe.hpp"

/*---------------CONSTRUCTOR----------------*/

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) {
	*this = other;
}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		*this = other;
	}
	return *this;
}

/*--------------------METHODS-----------------------*/

void PmergeMe::callVectSort(char** av)
{
	this->takeIputVec(av);
	if (this->vector.size() == 1) {
		bigChain.push_back(vector.at(0));
	} else {
		makeVecPair();
		sortVecPair();
		splitVecSort(vecPair, 0, vecPair.size() - 1);
		makeChain();
		insertion();
	}
}

void PmergeMe::takeIputVec(char** av)
{
	int i = 1;
	int val;
	while (av[i]) {
		if (av[i][0] == '\0') {
			throw std::invalid_argument("empty integer input!\n");
		}
		int j = 0;
		while (av[i][j]) {
			if (isdigit(av[i][j]) == false) {
				throw std::invalid_argument("invalid input, must be all digits\n");
				j++;
			}
		}
		val = std::stoi(av[i]);
		if (val < 0) {
			throw std::invalid_argument("input must be non-negative\n");
		}
		this->vector.push_back(val);
		i++;
	}
	// std::vector<int> tmp = this->vector;
	// std::sort(tmp.begin(), tmp.end());
	// for (size_t i = 0; i < tmp.size(); i++) {
	// 	if (tmp[i] == tmp[i + 1]) {
	// 		throw std::invalid_argument("duplication of number!");
	// 	}
	// }
}

void PmergeMe::makeVecPair()
{
	size_t size;
	int i;

	i = 0;
	size = this->vector.size() / 2;
	while (size != 0) {
		this->vecPair.push_back(std::make_pair(vector.at(i), vector.at(i + 1)));
		i += 2;
		size--;
	}
}

void PmergeMe::sortVecPair()
{
	size_t i;
	int tmp;

	i = 0;
	while (i < this->vecPair.size()) {
		if (vecPair.at(i).first < vecPair.at(i).second) {
			tmp = vecPair.at(i).first;
			vecPair.at(i).first = vecPair.at(i).second;
			vecPair.at(i).second = tmp;
		}
		i++;
	}
}

// splite arr into left and right halves, no sort
void PmergeMe::splitVecSort(std::vector<std::pair<int, int>>& arr, int st, int ed)
{
	if (st >= ed) {
		return ;
	}
	int mid = st + (ed - st) / 2;
	this->splitVecSort(arr, st, mid);
	this->splitVecSort(arr, mid + 1, ed);
	this->mergeVec(arr, st, mid, ed);
}

void PmergeMe::mergeVec(std::vector<std::pair<int, int>>& arr, int st, int mid, int ed)
{
	size_t l_idx;
	size_t r_idx;
	size_t i;

	// start ... mid
	std::vector<std::pair<int, int>> l_Part(arr.begin() + st, arr.begin() + mid + 1);
	// mid + 1 ... end
	std::vector<std::pair<int ,int>> r_Part(arr.begin() + mid + 1, arr.begin() + ed + 1);

	l_idx = 0;
	r_idx = 0;
	i = st; // i is at start

	// merge when both side has elements, compare current smallest elements from 2 sides
	// smaller one => arr[i]
	while (l_idx < l_Part.size() && r_idx < r_Part.size()) {
		// within range
		if (l_Part[l_idx].first <= r_Part[r_idx].first) {
			arr[i] = l_Part[l_idx];
			l_idx++;
		} else {
			arr[i] = r_Part[r_idx];
			r_idx++;
		}
		i++;
		while (l_idx < l_Part.size()) {
			arr[i] = l_Part[l_idx];
			l_idx++;
			i++;
		}
		while (r_idx < r_Part.size()) {
			arr[i] = r_Part[r_idx];
			r_idx++;
			i++;
		}
	}
}

void PmergeMe::makeChain()
{
	// make a1, b1, a2, a3, ... aN chain
	size_t i;
	bigChain.push_back(vecPair.at(0).second);
	i = 0;
	while (i < vecPair.size()) {
		bigChain.push_back(this->vecPair.at(i).first);
		smallChain.push_back(this->vecPair.at(i).second);
		i++;
	}
}

int PmergeMe::binSrchVec(std::vector<int> arr, int target, int st, int ed)
{
	int mid;

	while (st <= ed)
	{
		mid = st + (ed - st) / 2; // vs ()
		if (target == arr.at(mid)) {
			return mid;
		}
		if (target > arr.at(mid)) {
			st = mid + 1;
		} else {
			ed = mid - 1;
		}
	}
	if (target > arr.at(mid)) {
		return mid + 1;
	} else {
		return mid;
	}
}

// CORE part, jacob sequesce!
// 0, 1, 1, 3, 5, 11, 21
// j(0) = 0; j(1) = 1; j(n) = j(n-1) + 2j(n-2) for n>=2

int PmergeMe::calcuJknbr(int size)
{
	if (size == 0) {
		return 0; // return empty std::vector, cuz no element to insert!
	}
	if (size == 1) {
		return 1;
	}
	return (calcuJknbr(size - 1) + 2 * calcuJknbr(size - 2));
}

void PmergeMe::createJkOrder()
{
	size_t size;
	size_t jkIdx;
	int i;
	size = this->smallChain.size();
	i = 3; // 0 1 1 3 5 ...
	while ((jkIdx = this->calcuJknbr(i)) < size - 1) {
		this->jkOrder.push_back(jkIdx);
		i++;
	}
}

void PmergeMe::createInsrtOrder()
{
	if (smallChain.empty() == true) {
		return ;
	}
	this->createJkOrder(); // create jkOrder
	size_t pre_jkIdx = 1; // prev jk-idx used
	size_t cur_jkIdx = 0; // will be replace soon, just to init var
	size_t jkOrderIdx = 0; // to get the 'jkorder;, 0->3, 1->5, 3->11

	while (jkOrderIdx < this->jkOrder.size())
	{
		cur_jkIdx = jkOrder.at(jkOrderIdx); // take current jk number
		this->insrtPos.push_back(cur_jkIdx); // make it insertion index
		
		size_t backtrackIdx = cur_jkIdx - 1; // eg jk = 5, go 5 -> 4
		while (backtrackIdx > pre_jkIdx) {
			this->insrtPos.push_back(backtrackIdx);
			backtrackIdx--;
		}
		pre_jkIdx = cur_jkIdx;
		jkOrderIdx++;
	}
	while (++cur_jkIdx < this->smallChain.size()) {
		this->insrtPos.push_back(cur_jkIdx);
	}
}

void PmergeMe::insertion()
{
	int target;
	size_t curPos;
	this->createInsrtOrder();
	size_t added = 0;
	std::vector<int>::iterator it;
	for (it = this->insrtPos.begin(); it != this->insrtPos.end(); ++it)
	{
		size_t endPos = added + *it;
		target = this->smallChain.at(*it - 1); //check
		curPos = this->binSrchVec(this->bigChain, target, 0, endPos);
		this->bigChain.insert(this->bigChain.begin() + curPos, target);
		added++;
	}
	if (this->vector.size() % 2 != 0)
	{
		target = this->vector.at(this->vector.size() - 1);
		curPos = this->binSrchVec(this->bigChain, target, 0, this->bigChain.size() - 1);
		this->bigChain.insert(this->bigChain.begin() + curPos, target);
	}
}

void PmergeMe::printVec_b()
{
	for (size_t i = 0; i < this->vector.size(); ++i) {
		std::cout << vector.at(i) << " ";
	}
	std::cout << std::endl;
}
void PmergeMe::printVec_a()
{
	for (size_t i = 0; i < this->vector.size(); ++i) {
		std::cout << vector.at(i) << " ";
	}
	std::cout << std::endl;
}

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
