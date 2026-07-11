/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:56:58 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 20:24:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal()
	: type("Animal")
{
	std::cout << "Default Constructor : Animal" << std::endl;
}

Animal::Animal(const std::string& type)
	: type(type)
{
	std::cout << "Constructor : Animal - " << getType() << std::endl;
}

//캡슐화 및 컴파일러 자체 인라인 함수 생성으로 비용 최소화
Animal::Animal(const Animal& copy)
	: type(copy.getType())
{
	std::cout << "Copy Constructor : Animal - " << getType() << std::endl;
}

Animal::~Animal()
{
	std::cout << "Destructor : Animal" << std::endl;
}

Animal& Animal::operator=(const Animal& rhs)
{
	if (this != &rhs)
	{
		SetType(rhs.getType());
	}
	return (*this);
}

std::string Animal::getType() const
{
	return (type);
}

void Animal::SetType(const std::string& type)
{
	this->type = type;
}

void Animal::makeSound() const
{
	std::cout << "makeSound : Animal" << std::endl;
}
