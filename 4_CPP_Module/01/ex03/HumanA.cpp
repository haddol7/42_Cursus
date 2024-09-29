/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:11:27 by daeha             #+#    #+#             */
/*   Updated: 2024/09/29 23:08:50 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon& weapon)
	: name(name), weapon(weapon)
{
}

HumanA::~HumanA()
{
}

std::string HumanA::getName() const
{
	return (name);
}

void HumanA::attack()
{
	std::cout << getName() << " attacks with their " << weapon.getType() << std::endl;
}
