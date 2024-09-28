/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:06:24 by daeha             #+#    #+#             */
/*   Updated: 2024/09/29 00:05:27 by daeha            ###   ########.fr       */
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
	while (true)
	{
		std::cout << "> ";
		std::cin >> index;
		mContacts[index].displayContactInfo();
		break;
	}
}

void PhoneBook::displayProgram()
{
	std::string	cmd;
	
	do
	{	
		std::cout << "<ADD, SEARCH, EXIT>\n>";
		std::getline(std::cin, cmd);
		if (cmd == "ADD")
			addContact();
		else if (cmd == "SEARCH")
			searchContact();
	} while (cmd != "EXIT");
}
