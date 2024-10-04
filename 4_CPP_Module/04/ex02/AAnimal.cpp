/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:56:58 by daeha             #+#    #+#             */
/*   Updated: 2024/10/03 23:21:03 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal()
	: type("AAnimal")
{
	std::cout << "Constructor : AAnimal - " << getType() << std::endl;
}

AAnimal::AAnimal(const std::string& type)
	: type(type)
{
	std::cout << "Constructor : AAnimal" << std::endl;
}

//캡슐화 및 컴파일러 자체 인라인 함수 생성으로 비용 최소화
AAnimal::AAnimal(const AAnimal& copy)
	: type(copy.getType())
{
	std::cout << "Copy Constructor : AAnimal" << std::endl;
}

AAnimal::~AAnimal()
{
	std::cout << "Destructor : AAnimal" << std::endl;
}

AAnimal& AAnimal::operator=(const AAnimal& lhs)
{
	if (this != &lhs)
	{
		SetType(lhs.getType());
	}
	return (*this);
}

std::string AAnimal::getType() const
{
	return (type);
}

void AAnimal::SetType(const std::string& type)
{
	this->type = type;
}

void AAnimal::makeSound() const
{
	std::cout << "makeSound : AAnimal" << std::endl;
}
