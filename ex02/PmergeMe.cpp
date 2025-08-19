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

void PmergeMe::takeIputVec(char** av)
{
	int i = 1;
	int val;
	while (av[i]) {
		if (av[i] == '\0') {
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
	int i;
	int tmp;

	i = 0;
	while (i < vecPair.size()) {
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
	int l_idx;
	int r_idx;
	int i;

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

