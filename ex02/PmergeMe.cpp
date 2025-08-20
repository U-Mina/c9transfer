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
	// (void)other;
	return *this;
}

/*--------------------METHODS-----VECTOR------------------*/

void PmergeMe::callVectSort(char** av)
{
	this->takeIputVec(av);
	if (this->vector.size() == 1) {
		bigChain_v.push_back(this->vector.at(0));
	}
	else {
		this->makeVecPair();
		this->sortVecPair();
		this->splitVecSort(this->vecPair, 0, this->vecPair.size() - 1);
		this->makeVecChain();
		this->insertion_v();
	}
}

void PmergeMe::takeIputVec(char** av)
{
	int i;
	// char *p; //check: what p is doing
	int val;
	i = 1;
	while (av[i]) {
		if (av[i][0] == '\0') {
			throw std::invalid_argument("empty integer input!\n");
		}
		// int j = 0;
		// while (av[i][j]) {
		// 	if (isdigit(av[i][j]) == false) {
		// 		throw std::invalid_argument("invalid input, must be all digits\n");
		// 		j++;
		// 	}
		// }
		// val = std::strtol(av[i], &p, 10);
		val = std::atoi(av[i]);
		// if (*p != '\0' || val < 0) {
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
	while (size != 0)
	{
		this->vecPair.push_back(std::make_pair(this->vector.at(i), this->vector.at(i + 1)));
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
		if (this->vecPair.at(i).first < this->vecPair.at(i).second) {
			tmp = this->vecPair.at(i).first;
			this->vecPair.at(i).first = this->vecPair.at(i).second;
			this->vecPair.at(i).second = tmp;
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
	}
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

void PmergeMe::makeVecChain()
{
	// make a1, b1, a2, a3, ... aN chain
	size_t i;
	bigChain_v.push_back(this->vecPair.at(0).second);
	i = 0;
	while (i < this->vecPair.size()) {
		bigChain_v.push_back(this->vecPair.at(i).first);
		smallChain_v.push_back(this->vecPair.at(i).second);
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
		if (target > arr.at(mid))
		{
			st = mid + 1;
		} else {
			ed = mid - 1;
		}
	}
	if (target > arr.at(mid)) {
		return mid + 1;
	} else
	{
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
	size = this->smallChain_v.size();
	i = 3; // 0 1 1 3 5 ...
	while ((jkIdx = this->calcuJknbr(i)) < size - 1) {
		this->jkOrder.push_back(jkIdx);
		i++;
	}
}

void PmergeMe::createInsrtOrder()
{
	if (this->smallChain_v.empty() == true) {
		return ;
	}
	this->createJkOrder(); // create jkOrder
	size_t pre_jkIdx = 1; // prev jk-idx used
	size_t cur_jkIdx = 1; // will be replace soon, just to init var
	size_t jkOrderIdx = 0; // to get the 'jkorder;, 0->3, 1->5, 3->11
	// size_t backtrackIdx;

	while (jkOrderIdx < this->jkOrder.size())
	{
		cur_jkIdx = jkOrder.at(jkOrderIdx); // take current jk number
		this->insrtPos_v.push_back(cur_jkIdx); // make it insertion index
		
		size_t backtrackIdx = cur_jkIdx - 1; // eg jk = 5, go 5 -> 4
		while (backtrackIdx > pre_jkIdx) {
			this->insrtPos_v.push_back(backtrackIdx);
			backtrackIdx--;
		}
		pre_jkIdx = cur_jkIdx;
		jkOrderIdx++;
	}
	while (cur_jkIdx++ < this->smallChain_v.size()) {
		this->insrtPos_v.push_back(cur_jkIdx);
	}
}

void PmergeMe::insertion_v()
{
	int target;
	size_t curPos;
	this->createInsrtOrder();
	size_t added = 0;
	std::vector<int>::iterator it;
	for (it = this->insrtPos_v.begin(); it != this->insrtPos_v.end(); ++it)
	{
		size_t endPos = added + *it;
		target = this->smallChain_v.at(*it - 1); //check
		curPos = this->binSrchVec(this->bigChain_v, target, 0, endPos);
		this->bigChain_v.insert(this->bigChain_v.begin() + curPos, target);
		added++;
	}
	if (this->vector.size() % 2 != 0)
	{
		target = this->vector.at(this->vector.size() - 1);
		curPos = this->binSrchVec(this->bigChain_v, target, 0, this->bigChain_v.size() - 1);
		this->bigChain_v.insert(this->bigChain_v.begin() + curPos, target);
	}
}

void PmergeMe::printVec_b()
{
	std::cout << "Before is: ";
	for (size_t i = 0; i < this->vector.size(); ++i) {
		std::cout << this->vector.at(i) << " ";
		// std::cout << "print this";
	}
	std::cout << std::endl;
}
void PmergeMe::printVec_a()
{
	std::cout << "After is: ";
	for (size_t i = 0; i < this->bigChain_v.size(); ++i) {
		std::cout << bigChain_v.at(i) << " ";
	}
	std::cout << std::endl;
}

/*--------------------METHODS-----DEQUE------------------*/

void PmergeMe::callDeqSort(char** av)
{
	int val;
	for (int i = 1; av[i]; i++)
	{
		if (av[i][0] == '\0') {
			throw std::invalid_argument("Error: empty integer input!\n");
		}
		val = std::atol(av[i]);
		if (val < 0) {
			throw std::invalid_argument("Error: negetive input!\n");
		}
		this->deque.push_back(val);
	}
	std::deque<int> tmp = this->deque;
	std::sort(tmp.begin(), tmp.end());
	for (size_t j = 0; j < tmp.size(); j++) {
		if (tmp[j] == tmp[j + 1]) {
			throw std::invalid_argument("Error: duplication of number!");
		}
	}
}

void PmergeMe::makeDeqPair()
{
	size_t size;
	int i;

	i = 0;
	size = this->deque.size() / 2;
	while (size != 0)
	{
		this->deqPair.push_back(std::make_pair(this->deque.at(i), this->deque.at(i + 1)));
		i += 2;
		size--;
	}
}

void PmergeMe::sortDeqPair()
{
	size_t i;
	int tmp;

	i = 0;
	for (int i = 0; i < this->deqPair.size(); i++) {
	// while (i < this->deqPair.size()) {
		if (this->deqPair.at(i).first < this->deqPair.at(i).second) {
			tmp = this->deqPair.at(i).first;
			this->deqPair.at(i).first = this->deqPair.at(i).second;
			this->deqPair.at(i).second = tmp;
		}
		// i++;
	}
}

void PmergeMe::splitDeqSort(std::deque<std::pair<int, int>>& arr, int st, int ed)
{
	if (st >= ed) {
		return ;
	}
	int mid = st + (ed - st) / 2;
	this->splitDeqSort(arr, st, mid);
	this->splitDeqSort(arr, mid + 1, ed);
	this->mergeDeq(arr, st, mid, ed);
}

void PmergeMe::mergeDeq(std::deque<std::pair<int, int>>& arr, int st, int mid, int ed)
{
	size_t l_idx;
	size_t r_idx;
	size_t i;

	std::deque<std::pair<int, int>> l_Part(arr.begin() + st, arr.begin() + mid + 1);
	std::deque<std::pair<int ,int>> r_Part(arr.begin() + mid + 1, arr.begin() + ed + 1);

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
	}
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

void PmergeMe::makeDeqChain()
{
	// make a1, b1, a2, a3, ... aN chain
	size_t i;
	bigChain_d.push_back(this->deqPair.at(0).second);
	i = 0;
	while (i < this->deqPair.size()) {
		bigChain_d.push_back(this->deqPair.at(i).first);
		smallChain_d.push_back(this->deqPair.at(i).second);
		i++;
	}
}

int PmergeMe::binSrchDeq(std::deque<int> arr, int target, int st, int ed)
{
	int mid;

	while (st <= ed)
	{
		mid = st + (ed - st) / 2; // vs ()
		if (target == arr.at(mid)) {
			return mid;
		}
		if (target > arr.at(mid))
		{
			st = mid + 1;
		} else {
			ed = mid - 1;
		}
	}
	if (target > arr.at(mid)) {
		return mid + 1;
	} else
	{
		return mid;
	}
}

void PmergeMe::crtJkOrderDeq()
{
	size_t size;
	size_t jkIdx;
	int i;
	size = this->smallChain_d.size();
	i = 3; // 0 1 1 3 5 ...
	while ((jkIdx = this->calcuJknbr(i)) < size - 1) {
		this->jkOrder_d.push_back(jkIdx);
		i++;
	}
}

void PmergeMe::crtInsrtOrderDeq()
{
	if (this->smallChain_d.empty() == true) {
		return ;
	}
	this->crtInsrtOrderDeq(); // create jkOrder
	size_t pre_jkIdx = 1; // prev jk-idx used
	size_t cur_jkIdx = 1; // will be replace soon, just to init var
	//size_t jkOrderIdx = 0; // to get the 'jkorder;, 0->3, 1->5, 3->11
	size_t backtrackIdx;

	while (!this->jkOrder_d.empty())
	{
		cur_jkIdx = jkOrder_d.front();
		jkOrder_d.pop_front();
		insrtPos_d.push_back(cur_jkIdx);
		backtrackIdx = cur_jkIdx - 1;
		while (backtrackIdx > pre_jkIdx)
		{
			this->insrtPos_d.push_back(backtrackIdx);
			backtrackIdx--;
		}
		pre_jkIdx = cur_jkIdx;
		// jkOrder_d
	}
	while (cur_jkIdx++ < this->smallChain_d.size()) {
		this->insrtPos_d.push_back(cur_jkIdx);
	}
	// while (jkOrderIdx < this->jkOrder_d.size())
	// {
	// 	cur_jkIdx = jkOrder_d.at(jkOrderIdx); // take current jk number
	// 	this->insrtPos_d.push_back(cur_jkIdx); // make it insertion index
		
	// 	size_t backtrackIdx = cur_jkIdx - 1; // eg jk = 5, go 5 -> 4
	// 	while (backtrackIdx > pre_jkIdx) {
	// 		this->insrtPos_d.push_back(backtrackIdx);
	// 		backtrackIdx--;
	// 	}
	// 	pre_jkIdx = cur_jkIdx;
	// 	jkOrderIdx++;
	// }
	// while (cur_jkIdx++ < this->smallChain_d.size()) {
	// 	this->insrtPos_d.push_back(cur_jkIdx);
	// }
}
void PmergeMe::insertion_d()
{
	
}