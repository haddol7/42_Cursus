/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:06:24 by daeha             #+#    #+#             */
/*   Updated: 2024/10/05 01:30:10 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdio>
#include <limits>
#include "PhoneBook.hpp"

PhoneBook::PhoneBook() 
	: mIndex(0)
{
	std::cout << "Welcome" << std::endl;
}

PhoneBook::~PhoneBook()
{
	std::cout << "Bye" << std::endl;
}

//빈 문자열
void PhoneBook::addContact()
{
	if (mIndex == 2147483647)
	{
		mIndex = 7;
	}
	mContacts[mIndex % 8].setContactInfo(mIndex % 8);
	mIndex++;
}

void PhoneBook::searchContact()
{
	int	index;
	
	for (int i = 0; i < mIndex && i < 8; i++)
	{
		mContacts[i].displayContactInfo();	
	}
	std::cout << "============================" << std::endl;
	while (mIndex > 0)
	{
		std::cout << "Enter Index to see > " << std::flush;
		std::cin >> index;
		if (std::cin.good() && index >= 0 && index < 8 && index < mIndex)
		{
			mContacts[index].displayAllINFO();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
		else if (std::cin.fail() || std::cin.eof())
		{
			std::cin.clear();
			std::clearerr(stdin);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (std::cin.eof())
			{
				std::cout << std::endl;
			}
		}
	}
}

void PhoneBook::displayProgram()
{
	std::string	cmd;

	std::cout << "[ADD, SEARCH, EXIT]" << std::endl;
	do
	{
		std::cout << "MODE > " << std::flush;	
		std::getline(std::cin, cmd);
		if (std::cin.eof() || std::cin.fail())
		{
			std::cin.clear();
			std::clearerr(stdin);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (std::cin.eof())
			{
				std::cout << std::endl;
			}
			continue;
		}
		if (cmd == "ADD")
			addContact();
		else if (cmd == "SEARCH")
			searchContact();
	} while (cmd != "EXIT" || std::cin.bad());
}
