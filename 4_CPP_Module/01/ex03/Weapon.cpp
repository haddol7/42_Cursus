/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:05:10 by daeha             #+#    #+#             */
/*   Updated: 2024/09/29 22:59:35 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon()
	: type("default")
{
}

Weapon::Weapon(std::string name)
	: type(name)
{
}

Weapon::~Weapon()
{
}

const std::string& Weapon::getType()
{
	return (type);
}

void Weapon::setType(std::string name)
{
	type = name;
}
