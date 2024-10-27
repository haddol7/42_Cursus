#pragma once
#include <map>

class BitcoinExchange
{
public:
	BitcoinExchange();
	~BitcoinExchange();	
	BitcoinExchange(const BitcoinExchange& copy);
	BitcoinExchange& operator=(const BitcoinExchange& rhs);

	double	Exchange(const std::string& data_line);
	bool	IsValidDate(const std::string& date);
	bool	IsValidFormat(const std::string& data_line);

private:
	std::map <const std::string, const float> mDatabase;
};
