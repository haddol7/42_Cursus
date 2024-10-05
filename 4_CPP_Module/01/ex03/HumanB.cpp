/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:49:35 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 00:44:12 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name)
	: name(name)
	, weapon(0)
{
}

HumanB::~HumanB()
{
}

std::string HumanB::getName() const
{
	return (name);
}

void HumanB::setWeapon(Weapon& weapon)
{
	this->weapon = &weapon;
}

void HumanB::attack()
{
	if (weapon != 0)
	{
		std::cout << getName() << " attacks with their " << weapon->getType() << std::endl;
	}
	else
	{
		std::cout << getName() << " doesn't have weapon" << std::endl;
	}
}

