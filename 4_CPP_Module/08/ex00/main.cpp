#include <iostream>
#include <vector>
#include <deque>
#include "easyfind.hpp"

int main()
{
	std::vector<int>			test_vector;
	std::deque<int>				test_deque;

	test_vector.reserve(10);
	for (int i = 0; i < 10; ++i)
	{
		test_vector.push_back(i);
		test_deque.push_back(i);
	}
	test_vector[5] = 42;
	test_vector[9] = 42;

	std::vector<int>::iterator it_vector = easyfind(test_vector, 42);
	std::deque<int>::iterator it_deque = easyfind(test_deque, 42);

	if (it_vector != test_vector.end())
	{
		std::cout << "i found vector " << *it_vector << std::endl;
	}
	if (it_deque == test_deque.end())
	{
		std::cout << "i can't find deque" << std::endl;
	}
}
