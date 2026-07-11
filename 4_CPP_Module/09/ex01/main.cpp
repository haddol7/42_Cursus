#include <iostream>
#include "RPN.hpp"

int print_error(void);

int main(int argc, char *argv[])
{
	RPN		calculator;
	char	token;
	
	if (argc != 2)
	{
		return (print_error());
	}
	for (int i = 0; argv[1][i] != '\0'; ++i)
	{	
		token = argv[1][i];
		if (i % 2 == 1)
		{
			if (token != ' ')
			{
				return (print_error());
			}
			continue;
		}
		else if (calculator.PushTokenAndCalculate(token) == false)
		{
			return (print_error());
		}
	}
	if (calculator.GetSize() != 1)
	{
		return (print_error());
	}
	std::cout << calculator.GetResult() << std::endl;
	return (0);
}

int print_error(void)
{
	std::cout << "Error" << std::endl;
	return (1);
}
