#include <exception>
#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

# define COMMA (10)

BitcoinExchange::BitcoinExchange()
{
	std::ifstream	fin("data.csv");
	std::string		data_line;

	if (fin.bad() || fin.fail())
	{
		throw std::runtime_error("can't open as Database.");
	}
	getline(fin, data_line);
	if (data_line != "date,exchange_rate")
	{
		throw std::runtime_error("header must be \"date,exchange_rate\".");
	}
	size_t	pos;
	while (fin.eof() == false)
	{
		getline(fin, data_line);
		pos = data_line.rfind(",");
		if (pos != COMMA || IsValidDate(data_line) == false)
		{
			throw std::runtime_error("date must be \"20XX-XX-XX,value\".");
		}
		mDatabase.insert(std::pair<std::string, float>(data_line.substr(0, pos), atof(data_line.substr(pos + 1).c_str())));
	}
	fin.close();
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy)
{
	mDatabase = copy.mDatabase;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs)
{
	if (this != &rhs)
	{
		mDatabase = rhs.mDatabase;
	}
	return (*this);
}

double	BitcoinExchange::Exchange(const std::string& data_line)
{
	double	value;
	std::string	date;
	std::string	value_str;

	if (IsValidFormat(data_line) == false)
	{
		std::cout << "Error : invalid format => " << data_line << std::endl;
		return (-1);
	}
	date = data_line.substr(0, 10);
	value_str = data_line.substr(14);
	value = atof(value_str.c_str());
	if (IsValidDate(date) == false)
	{
		std::cout << "Error : invalid format => " << data_line << std::endl;
		return (-1);
	}
	else if (value < 0)
	{
		std::cout << "Error : invalid format => " << data_line << std::endl;
		return (-1);
	}
	else if (value > 1000)
	{
		std::cout << "Error : invalid format => " << data_line << std::endl;
		return (-1);
	}
	for (std::map<const std::string, const float>::iterator it = mDatabase.begin(); it != mDatabase.end(); ++it)
	{
		if (date < it->first)
		{
			if (it == mDatabase.begin())
			{
				std::cout << "Error : There is no data before => " << date << std::endl;
				return (-1);
			}
			value *= it->second;
			break;
		}
	}
	return (value);
}

// 윤달
bool	BitcoinExchange::IsValidDate(const std::string& date)
{
	if (date.empty() == true)
	{
		return (false);
	}
	return (true);
}

//2011-01-03 | 3
bool BitcoinExchange::IsValidFormat(const std::string& data_line) 
{
	if (data_line.length() < 14)
	{
		return (false);
	}
	if (data_line[4] != '-' || data_line[7] != '-' || data_line[10] != ' ' || data_line[13] != '|') 
	{
		return (false);
	}
	for (int i = 0; i < 4; ++i) 
	{
		if (!isdigit(data_line[i])) 
		{
			return (false);
		}
	}
	for (int i = 5; i < 7; ++i) 
	{
		if (!isdigit(data_line[i]) || !isdigit(data_line[i + 3]))
		{
			return (false);
		}
	}
    for (int i = 12; data_line[i] != '\0'; ++i)
	{
        if (!isdigit(data_line[i]))
		{
			return (false);
		}
    }
    return true;
}
