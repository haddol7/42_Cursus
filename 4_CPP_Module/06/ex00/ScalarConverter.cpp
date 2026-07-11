#include <iostream>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <cerrno>
#include "ScalarConverter.hpp"


/*
char	->	'value'	/ Non displayable	/ impossible
int		->	value	/ impossible
float	->	valuef	/ nanf /	+inff	/	-inff
double	->	value	/ nan  /	+inf	/	-inf
*/

/*
340282346638528859811704183484516925440.0
-340282346638528859811704183484516925440.0
*/

void ScalarConverter::convert(const std::string& str)
{
	const std::string	psuedo_literals[6] = {"nan", "nanf", "+inf", "+inff", "-inf", "-inff"};
	const char*	const	cstr = str.c_str();
	char*				end;
	double				dvalue = strtod(cstr, &end);

	for (int i_literal = 0; i_literal < 6; ++i_literal)
	{
		if (str == psuedo_literals[i_literal])
		{
			std::cout << "char : impossible" << std::endl;
			std::cout << "int : impossible" << std::endl;
			std::cout << "float : " << psuedo_literals[i_literal + ((i_literal & 1) ^ 1)] << std::endl;
			std::cout << "double : " << psuedo_literals[i_literal - (i_literal & 1)] << std::endl;
			return ;
		}
	}
	if ((*end != '\0' && strcmp(end, "f") != 0) || errno == ERANGE)
	{
		std::cout << "char : impossible" << std::endl;
		std::cout << "int : impossible" << std::endl;
		std::cout << "float : impossible " << std::endl;
		std::cout << "double : impossible " << std::endl;
		return ;
	}

	std::cout << "char : ";
	if (isprint(static_cast<int>(dvalue)) == true)
	{
		std::cout << "'" << static_cast<char>(dvalue) << "'";
	}
	else if (dvalue != static_cast<char>(dvalue))
	{
		std::cout << "Non displayable";
	}
	else
	{
		std::cout << "impossible";
	}
	std::cout << std::endl;

	std::cout << "int : ";
	if (static_cast<long>(dvalue) == static_cast<int>(dvalue))
	{
		std::cout << static_cast<int>(dvalue);
	}
	else
	{
		std::cout << "impossible";
	}
	std::cout << std::endl;

	std::cout << "float : ";
	if (std::numeric_limits<float>::max() >= dvalue && std::numeric_limits<float>::min() <= dvalue)
	{
		std::cout << std::fixed << std::setprecision(1) << static_cast<float>(dvalue) << "f";
	}
	else
	{
		std::cout << "impossible";
	}
	std::cout << std::endl;
	
	std::cout << "double : " << std::fixed << std::setprecision(1) << dvalue << std::endl;
} 

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter& copy)
{
	if (this != &copy)
	{
	}
	return ;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& rhs)
{
	if (this != &rhs)
	{
	}
	return (*this);
}
