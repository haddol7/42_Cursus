/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:56:58 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 20:24:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
	: type("WrongAnimal")
{
	std::cout << "Default Constructor : WrongAnimal" << std::endl;
}

WrongAnimal::WrongAnimal(const std::string& type)
	: type(type)
{
	std::cout << "Constructor : WrongAnimal - " << getType() << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& copy)
	: type(copy.getType())
{
	std::cout << "Copy Constructor : WrongAnimal - " << getType() << std::endl;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "Destructor : WrongAnimal" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& rhs)
{
	if (this != &rhs)
	{
		SetType(rhs.getType());
	}
	return (*this);
}

std::string WrongAnimal::getType() const
{
	return (type);
}

void WrongAnimal::SetType(const std::string& type)
{
	this->type = type;
}

void WrongAnimal::makeSound() const
{
	std::cout << "makeSound : WrongAnimal" << std::endl;
}
