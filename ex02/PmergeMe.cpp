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

void PmergeMe::mergeVec(std::vector<std::pair<int, int>>& arr, int st, int mid, int ed)
{
	int l_idx;
	int r_idx;
	int i;
}