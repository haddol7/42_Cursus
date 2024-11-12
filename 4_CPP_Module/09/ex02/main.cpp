#include <iostream>
#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
	try
	{
		PmergeMe ford_johnson(argc, argv);

		ford_johnson.sort();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	return (0);
}
