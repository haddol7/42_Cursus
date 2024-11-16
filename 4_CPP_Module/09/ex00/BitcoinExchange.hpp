#pragma once
#include <map>

class BitcoinExchange
{
public:
	BitcoinExchange();
	~BitcoinExchange();	

	void	DisplayPrice(const std::string& data_line);
	bool	IsValidDate(const std::string& date);
	bool	IsValidFormat(const std::string& data_line, int mode);

private:
	BitcoinExchange(const BitcoinExchange& copy);
	BitcoinExchange& operator=(const BitcoinExchange& rhs);
	
	std::map <std::string, float> mDatabase;
};
