#include "easyfind.hpp"

template <typename T>
typename T::iterator easyfind(T& list, int target)
{
	return (std::find(list.begin(), list.end(), target));
}
