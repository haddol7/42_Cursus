#include <exception>
#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

# define COMMA (10)
# define DATABASE_MODE (0)
# define INPUT_MODE (2)

BitcoinExchange::BitcoinExchange()
{
	std::ifstream	fin("data.csv");
	std::string		data_line;

	if (fin.bad() || fin.fail())
	{
		throw std::runtime_error("Error: could not open data.csv");
	}
	getline(fin, data_line);
	if (data_line != "date,exchange_rate")
	{
		throw std::runtime_error("Error: header must be \"date,exchange_rate\" in data.csv");
	}
	while (true)
	{
		getline(fin, data_line);
		if (fin.eof() || fin.fail() || fin.bad())
		{
			break;
		}
		if (!IsValidFormat(data_line, DATABASE_MODE) || !IsValidDate(data_line))
		{
			throw std::runtime_error(data_line);
		}
		mDatabase.insert(std::pair<std::string, float>(data_line.substr(0, COMMA), atof(data_line.substr(COMMA + 1).c_str())));
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

void	BitcoinExchange::DisplayPrice(const std::string& data_line)
{
	double	value;
	std::string	date;
	std::string	value_str;

	if (IsValidFormat(data_line, INPUT_MODE) == false)
	{
		std::cout << "Error : invalid format => " << data_line << std::endl;
		return ;
	}
	date = data_line.substr(0, 10);
	value_str = data_line.substr(13);
	value = atof(value_str.c_str());
	if (!IsValidDate(date))
	{
		std::cout << "Error : bad input => " << data_line << std::endl;
		return ;
	}
	else if (value < 0)
	{
		std::cout << "Error : not a positive number." << std::endl;
		return ;
	}
	else if (value > 1000)
	{
		std::cout << "Error : too large a number." << std::endl;
		return ;
	}
	std::map<const std::string, const float>::iterator it = mDatabase.lower_bound(date);
	if (it == mDatabase.begin())
	{
		std::cout << "Error : There is no data before => " << date << std::endl;
		return ;
	}
	if (it == mDatabase.end() || date != it->first)
	{
		--it;
	}
	std::cout << date << " => " << value << " = " << value * it->second << std::endl;
}

// 1. 양력에서의 윤년 규칙
// 양력(그레고리력)에서는 윤년을 통해 추가적인 하루(2월 29일)를 넣어 연간 일수를 365일에서 366일로 만듭니다. 윤년은 다음 규칙에 따라 결정됩니다:
// 4로 나누어지는 해는 윤년입니다.
// 100으로 나누어지는 해는 평년입니다. (예: 1900년, 2100년 등)
// 400으로 나누어지는 해는 윤년입니다. (예: 1600년, 2000년 등)
bool	BitcoinExchange::IsValidDate(const std::string& date)
{
	const static int gregory[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int year = atoi(date.c_str());
	int month = atoi(date.c_str() + 5);
	int day = atoi(date.c_str() + 8);

	if (month < 1 || month > 12)
	{
		return (false);
	}

	int last_day = gregory[month - 1];
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
	{
		last_day = 29;
	}
	if (day < 1 || day > last_day)
	{
		return (false);
	}
	return (true);
}

//2011-01-03 | 3 	=> 14
//2011-12-27,4		=> 12
bool BitcoinExchange::IsValidFormat(const std::string& data_line, int mode) 
{
	if (data_line.length() < static_cast<size_t>(12 + mode))
	{
		return (false);
	}
	if (data_line[4] != '-' || data_line[7] != '-') 
	{
		return (false);
	}
	if ((mode == INPUT_MODE && (data_line[10] != ' ' || data_line[11] != '|' || data_line[12] != ' ')) ||\
		(mode == DATABASE_MODE && (data_line[10] != ',')))
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
	bool	is_float = false;
	int		pos_num = 11 + mode;
	for (int i = pos_num; data_line[i] != '\0'; ++i)
	{
		if (!isdigit(data_line[i]) && !(data_line[i] == '-' && i == pos_num))
		{
			if (data_line[i] == '.' && is_float == false && i > pos_num)
			{
				is_float = true;
				continue ;
			}
			return (false);
		}
	}
	return (true);
}
