/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:08:08 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 22:12:09 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
	: AAnimal("Cat")
{
	std::cout << "Constructor : Cat - " << getType() << std::endl;
	mBrain = new Brain;
}

Cat::~Cat()
{
	std::cout << "Destructor : Cat" << std::endl;
	delete mBrain;
	//std::cout << getType() << std::endl;
}

Cat::Cat(const Cat& copy)
	: AAnimal(copy.getType())
{
	std::cout << "Copy Constructor : Cat " << getType() << std::endl;
	mBrain = new Brain();
	*mBrain = *copy.mBrain;
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

const std::string& Cat::getBrainIdea(const int idx) const
{
	return (mBrain->getIdea(idx));
}

void Cat::setBrainIdea(const int idx, const std::string& str)
{
	mBrain->setIdea(idx, str);
}
