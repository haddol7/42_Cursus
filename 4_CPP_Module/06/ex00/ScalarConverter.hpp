#pragma once

#include <string>

class ScalarConverter
{
public:
	static void	convert(const std::string& string);

private:
	ScalarConverter();
	~ScalarConverter();
	ScalarConverter(const ScalarConverter& copy);
	ScalarConverter& operator=(const ScalarConverter& rhs);
};
