/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:06:20 by daeha             #+#    #+#             */
/*   Updated: 2024/09/29 14:11:56 by daeha            ###   ########.fr       */
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

private:
	int			mIndex;
	std::string mFirstName;
	std::string mLastName;
	std::string mNickName;
	std::string mPhoneNumber;
	std::string mDarkestSecret;
	void setStringIgnoreEOF(std::string &str) const;
	void displayFormattedString(const std::string& str) const;
};
