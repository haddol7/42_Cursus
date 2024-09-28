/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:03:42 by daeha             #+#    #+#             */
/*   Updated: 2024/09/29 00:06:52 by daeha            ###   ########.fr       */
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

void Contact::setContactInfo(int index)
{
	mIndex = index;
	std::cout << "First Name : ";
	getline(std::cin, mFirstName);
	std::cout << mFirstName << std::endl;
	// std::cin.ignore();
	std::cout << "Last Name : ";
	getline(std::cin, mLastName);
	// std::cin.ignore();
	std::cout << "Nickname : ";
	getline(std::cin, mNickName);
	// std::cin.ignore();
	std::cout << "Phone number : ";
	getline(std::cin, mPhoneNumber);
	// std::cin.ignore();
	std::cout << "Darkest secret : ";
	getline(std::cin, mDarkestSecret);
	// std::cin.ignore();
};

void Contact::displayContactInfo() const
{
	std::cout << std::right << std::setw(10);
	std::cout << mIndex;
	std::cout << "|";

	std::cout << std::right << std::setw(10);
	if (mFirstName.size() >= 10)
		std::cout << mFirstName.substr(0, 9) << ".";
	else
		std::cout << mFirstName;

	std::cout << "|";
	std::cout << std::right << std::setw(10);
	if (mLastName.size() >= 10)
		std::cout << mLastName.substr(0, 9) << ".";
	else
		std::cout << mLastName;

	std::cout << "|";	
	std::cout << std::right << std::setw(10);
	if (mNickName.size() >= 10)
		std::cout << mNickName.substr(0, 9) << ".";
	else
		std::cout << mNickName;
	std::cout << std::endl;
};
