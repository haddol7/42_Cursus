#include <iostream>
#include "iter.hpp"

template <typename T>
void	print(T a)
{
	std::cout << a << std::endl;
}

void	const_print(const int a)
{
	std::cout << a << std::endl;
}


void	change_elem(std::string& str)
{
	str = "test";
}

int main(void)
{
	int			ary[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::string	str[10];

	iter(ary, 10, print<int>);
	iter(ary, 10, const_print);
	iter(str, 10, change_elem);
	iter(str, 10, print<const std::string&>);
	return (0);
}
