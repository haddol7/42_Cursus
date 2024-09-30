/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:06:24 by daeha             #+#    #+#             */
/*   Updated: 2024/09/29 14:00:19 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() 
	: mIndex(0)
{
}

PhoneBook::~PhoneBook()
{
}

void PhoneBook::addContact()
{
	if (mIndex == INT_MAX)
		mIndex = 7;
	mContacts[mIndex % 8].setContactInfo(mIndex % 8);
	mIndex++;
}

void PhoneBook::searchContact()
{
	int	index;
	
	for (int i = 0; i < mIndex && i < 8; i++)
		mContacts[i].displayContactInfo();
	while (mIndex > 0)
	{
		std::cout << "> ";
		std::cin >> index;
		if (std::cin.good() && index >= 0 && index < 8 && index < mIndex)
		{
			mContacts[index].displayContactInfo();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
		else if (std::cin.fail() || std::cin.eof())
		{
			std::cin.clear();
			std::clearerr(stdin);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}

void PhoneBook::displayProgram()
{
	std::string	cmd;

	do
	{	
		std::cout << "[ADD, SEARCH, EXIT]" << std::endl << "$>";
		std::getline(std::cin, cmd);
		if (std::cin.eof() || std::cin.fail())
		{
			std::cin.clear();
			std::clearerr(stdin);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl;
			continue;
		}
		if (cmd == "ADD")
			addContact();
		else if (cmd == "SEARCH")
			searchContact();
	} while (cmd != "EXIT" || std::cin.bad());
}
