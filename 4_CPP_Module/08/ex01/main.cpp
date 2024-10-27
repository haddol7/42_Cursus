#include <iostream>
#include "Span.hpp"

int main()
{
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	return (0);
}

/*
#include <cstdlib>
#include <ctime>
#include <limits.h>
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "./ex02 <capacity>" << std::endl;
		return (1);
	}

	std::srand(static_cast<unsigned int>(std::time(0)));
	Span	span(atoi(argv[1]));
	int		random;

	for (int i = 0; i < atoi(argv[1]); ++i)
	{
		random = std::rand();
		span.addNumber(random);
		std::cout << random << " ";
	}
	std::cout << std::endl << std::endl;
	std::cout << span.shortestSpan() << " " << span.longestSpan() << std::endl;
	return (0);
}
*/

