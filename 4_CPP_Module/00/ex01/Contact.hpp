/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:06:20 by daeha             #+#    #+#             */
/*   Updated: 2024/10/05 01:03:32 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Contact
{
public:
	Contact();
	~Contact();
	void setContactInfo(int index);
	void displayContactInfo() const;
	void displayAllINFO() const;

private:
	int			mIndex;
	std::string mFirstName;
	std::string mLastName;
	std::string mNickName;
	std::string mPhoneNumber;
	std::string mDarkestSecret;
	void setStringIgnoreEOF(const std::string& msg, std::string &str) const;
	void displayFormattedString(const std::string& str) const;
};
