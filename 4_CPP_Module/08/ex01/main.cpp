#include <iostream>
#include "Span.hpp"

// int main()
// {
// 	Span sp = Span(5);
// 	sp.addNumber(6);
// 	sp.addNumber(3);
// 	sp.addNumber(17);
// 	sp.addNumber(9);
// 	sp.addNumber(11);
// 	std::cout << sp.shortestSpan() << std::endl;
// 	std::cout << sp.longestSpan() << std::endl;
// 	return (0);
// }

#include <cstdlib>
#include <ctime>
#include <limits.h>
int main(int argc, char *argv[])
{
	if (argc != 2 || atoi(argv[1]) <= 0)
	{
		std::cerr << "./ex02 <capacity> or invalid value" << std::endl;
		return (1);
	}
	try
	{
		Span				span(atoi(argv[1]));
		int					random;
		std::vector<int>	vec;

		std::srand(static_cast<unsigned int>(std::time(0)));
		for (int i = 0; i < atoi(argv[1]); ++i)
		{
			random = std::rand() % 10000;
			vec.push_back(random);
			std::cout << random << " ";
		}
		span.addNumbers(vec.begin(), vec.end());
		std::cout << std::endl << std::endl;
		std::cout << span.shortestSpan() << " " << span.longestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	return (0);
}


