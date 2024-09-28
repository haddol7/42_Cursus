/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:06:27 by daeha             #+#    #+#             */
/*   Updated: 2024/09/28 23:53:17 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Contact.hpp"

class PhoneBook
{
public:
	PhoneBook();
	~PhoneBook();
	void addContact();
	void searchContact();
	void displayProgram();
private:
	Contact mContacts[8];
	int		mIndex;
};
