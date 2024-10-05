/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:03:42 by daeha             #+#    #+#             */
/*   Updated: 2024/10/05 23:49:51 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdio>
#include <cctype>
#include <limits>
#include <iomanip>
#include "Contact.hpp"

Contact::Contact()
{
}

Contact::~Contact()
{
}

void Contact::setStringIgnoreEOF(const std::string& msg, std::string &str) const
{
	bool	isWritable = false;
	do
	{
		std::cout << msg << std::flush;
		getline(std::cin, str);
		if (std::cin.eof() || std::cin.fail())
		{
			std::cin.clear();
			std::clearerr(stdin);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl;
		}
		else
		{
			for (std::size_t i = 0; i < str.length(); i++)
			{
				if (isprint(static_cast<unsigned char>(str[i])) &&
					!isspace(static_cast<unsigned char>(str[i])))
				{
					isWritable = true;
				}
				if (str[i] == '\t')
				{
					str.replace(i, 1, " ");
				}
			}
		}
	} while (isWritable == false);
}
void Contact::displayFormattedString(const std::string& str) const
{
	std::cout << std::right << std::setw(10);
	if (str.size() > 10)
		std::cout << str.substr(0, 9) + ".";
	else
		std::cout << str;
	std::cout << "|";
}

void Contact::setContactInfo(int index)
{
	mIndex = index;
	setStringIgnoreEOF("First Name > ", mFirstName);
	setStringIgnoreEOF("Last Name > ", mLastName);
	setStringIgnoreEOF("Nickname > ", mNickName);
	setStringIgnoreEOF("Phone number > ", mPhoneNumber);
	setStringIgnoreEOF("Darkest secret > ", mDarkestSecret);
};

void Contact::displayContactInfo() const
{
	std::cout << std::right << std::setw(10);
	std::cout << mIndex;
	std::cout << "|";
	displayFormattedString(mFirstName);
	displayFormattedString(mLastName);
	displayFormattedString(mNickName);
	std::cout << std::endl;
};

void Contact::displayAllINFO() const
{
	std::cout << "============================" << std::endl;
	std::cout << "First name : " << mFirstName << std::endl;
	std::cout << "Last Name : " << mLastName << std::endl;
	std::cout << "NickName : " << mNickName << std::endl;
	std::cout << "Phone Number : " << mPhoneNumber << std::endl;
	std::cout << "Darkest Secret : " << mDarkestSecret << std::endl;
	std::cout << "============================" << std::endl;
}
