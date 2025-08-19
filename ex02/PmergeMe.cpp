#include "PmergeMe.hpp"

/*---------------CONSTRUCTOR----------------*/
template <typename T, template <typename , typename> class Container>
PmergeMe<T, Container>::PmergeMe() {}

template <typename T, template <typename , typename> class Container>
PmergeMe<T, Container>::PmergeMe(const PmergeMe<T, Container>& other) {
	*this = other;
}
template <typename T, template <typename , typename> class Container>
PmergeMe<T, Container>::~PmergeMe() {}

template <typename T, template <typename , typename> class Container>
PmergeMe<T, Container>& PmergeMe<T, Container>::operator=(const PmergeMe<T, Container>& other) {
	if (this != &other) {
		*this = other;
	}
	return *this;
}

/*--------------------METHODS-----------------------*/

template <typename T, template <typename , typename> class Container>
typename PmergeMe <T, Container>::ContainerType
PmergeMe<T, Container>::merging(ContainerType t1, ContainerType t2) const
{
	Container<std::pair<T, T>, std::allocator<T>> pairs;
	
}

template <typename T, template <typename , typename> class Container>
typename PmergeMe <T, Container>::ContainerType
PmergeMe<T, Container>::sorting(const ContainerType& arr) const
{
	
}