/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:08:08 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 20:24:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
	: Animal("Cat")
{
	std::cout << "Default Constructor : Cat" << std::endl;
	mBrain = new Brain;
}

Cat::~Cat()
{
	std::cout << "Destructor : Cat" << std::endl;
	delete mBrain;
}

Cat::Cat(const Cat& copy)
	: Animal(copy.getType())
{
	std::cout << "Copy Constructor : Cat " << getType() << std::endl;
	mBrain = new Brain(*copy.mBrain);
}

Cat& Cat::operator=(const Cat& rhs)
{
	if (this != &rhs)
	{
		SetType(rhs.getType());
		*mBrain = *rhs.mBrain;
	}
	return (*this);
}

void Cat::makeSound() const
{
	std::cout << getType() << " - meow meow" << std::endl;
}
