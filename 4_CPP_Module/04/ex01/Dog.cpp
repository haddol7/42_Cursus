/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:08:08 by daeha             #+#    #+#             */
/*   Updated: 2024/10/03 23:09:38 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
	: Animal("Dog")
{
	std::cout << "Constructor : Dog - " << getType() << std::endl;
	mBrain = new Brain;
}

Dog::~Dog()
{
	std::cout << "Destructor : Dog" << std::endl;
	delete mBrain;
	//std::cout << getType() << std::endl;
}

Dog::Dog(const Dog& copy)
	: Animal(copy.getType())
{
	std::cout << "Copy Constructor : Dog " << getType() << std::endl;
	mBrain = new Brain;
	*mBrain = *copy.mBrain;
}

Dog& Dog::operator=(const Dog& lhs)
{
	if (this != &lhs)
	{
		SetType(lhs.getType());
		*mBrain = *lhs.mBrain;
	}
	return (*this);
}

void Dog::makeSound() const
{
	std::cout << getType() << " - woof woof" << std::endl;
}
