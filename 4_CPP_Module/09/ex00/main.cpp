#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return (1);
	}
	std::ifstream file(argv[1]);
	if (file.fail() || file.bad())
	{
		std::cout << "Error: could not open file." << std::endl;
		return (1);
	}
	std::string		line;
	BitcoinExchange *database;
	try
	{
		database = new BitcoinExchange();
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: Database has error =>" << e.what() << '\n';
		return (1);
	}
	
	getline(file, line);
	if (line != "date | value")
	{
		std::cout << "Error: could not open file." << std::endl;
		delete database;
		file.close();
		return (1);
	}
	while (true)
	{
		getline(file, line);
		if (file.eof() || file.fail() || file.bad())
		{
			break ;
		}
		database->DisplayPrice(line);
	}
	
	delete database;
	file.close();
	return (0);
}
