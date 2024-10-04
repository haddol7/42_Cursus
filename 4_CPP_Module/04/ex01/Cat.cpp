/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:08:08 by daeha             #+#    #+#             */
/*   Updated: 2024/10/03 23:08:34 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
	: Animal("Cat")
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
	: Animal(copy.getType())
{
	std::cout << "Copy Constructor : Cat " << getType() << std::endl;
	mBrain = new Brain();
	*mBrain = *copy.mBrain;
}

Cat& Cat::operator=(const Cat& lhs)
{
	if (this != &lhs)
	{
		SetType(lhs.getType());
		*mBrain = *lhs.mBrain;
	}
	return (*this);
}

void Cat::makeSound() const
{
	std::cout << getType() << " - meow meow" << std::endl;
}
