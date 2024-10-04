/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:08:08 by daeha             #+#    #+#             */
/*   Updated: 2024/10/03 22:15:07 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat()
	: WrongAnimal("WrongCat")
{
	std::cout << "Constructor : WrongCat - " << getType() << std::endl;
}

WrongCat::~WrongCat()
{
	std::cout << "Destructor : WrongCat" << std::endl;
	//std::cout << getType() << std::endl;
}

WrongCat::WrongCat(const WrongCat& copy)
	: WrongAnimal(copy.getType())
{
	std::cout << "Copy Constructor : WrongCat " << getType() << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& lhs)
{
	if (this != &lhs)
	{
		SetType(lhs.getType());
	}
	return (*this);
}

void WrongCat::makeSound() const
{
	std::cout << getType() << " - meow meow" << std::endl;
}
