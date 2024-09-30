/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:03:42 by daeha             #+#    #+#             */
/*   Updated: 2024/09/29 14:47:11 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include "Contact.hpp"

Contact::Contact()
{
}

Contact::~Contact()
{
}

void Contact::setStringIgnoreEOF(std::string &str) const
{
	getline(std::cin, str);
	if (std::cin.eof() || std::cin.fail())
	{
		std::cin.clear();
		std::clearerr(stdin);
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
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
	std::cout << "First Name > ";
	setStringIgnoreEOF(mFirstName);
	std::cout << "Last Name > ";
	setStringIgnoreEOF(mLastName);
	std::cout << "Nickname > ";
	setStringIgnoreEOF(mNickName);
	std::cout << "Phone number > ";
	setStringIgnoreEOF(mPhoneNumber);
	std::cout << "Darkest secret > ";
	setStringIgnoreEOF(mDarkestSecret);
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
