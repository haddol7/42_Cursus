/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:08:08 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 21:42:27 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
	: Animal("Dog")
{
	std::cout << "Default Constructor : Dog" << std::endl;
	mBrain = new Brain;
}

Dog::~Dog()
{
	std::cout << "Destructor : Dog" << std::endl;
	delete mBrain;
}

Dog::Dog(const Dog& copy)
	: Animal(copy.getType())
{
	std::cout << "Copy Constructor : Dog " << getType() << std::endl;
	mBrain = new Brain(*copy.mBrain);
}

Dog& Dog::operator=(const Dog& rhs)
{
	if (this != &rhs)
	{
		SetType(rhs.getType());
		*mBrain = *rhs.mBrain;
	}
	return (*this);
}

void Dog::makeSound() const
{
	std::cout << getType() << " - woof woof" << std::endl;
}

const std::string& Dog::getBrainIdea(const int idx) const
{
	return (mBrain->getIdea(idx));
}

void Dog::setBrainIdea(const int idx, const std::string& str)
{
	mBrain->setIdea(idx, str);
}
