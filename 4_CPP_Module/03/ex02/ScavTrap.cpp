/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:42:41 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 02:01:16 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
	: ClapTrap("defualt", 100, 50, 20)
{
	std::cout << "ScavTrap Constructor : default" << std::endl;
}

ScavTrap::ScavTrap(const std::string& name)
	: ClapTrap(name, 100, 50, 20)
{
	std::cout << "ScavTrap Constructor : " << name << std::endl;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap Destructor : " << mName << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& copy)
	: ClapTrap(copy.mName, copy.mHitPoints, copy.mEnergyPoints, copy.mAttackDamage)
{
	std::cout << "ScavTrap Copy Constructor : " << mName << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& rhs)
{
	if (this != &rhs)
	{
		mName = rhs.mName; 
		mHitPoints = rhs.mHitPoints;
		mEnergyPoints = rhs.mEnergyPoints;
		mAttackDamage = rhs.mAttackDamage;
	}
	return (*this);
}

void ScavTrap::attack(const std::string& target)
{
	if (mHitPoints <= 0 || mEnergyPoints <= 0)
	{
		return ;
	}
	std::cout << "ScavTrap " << mName << " attacks " << target << ", causing " << mAttackDamage << " points of damage!" << std::endl;
	mEnergyPoints--;
}

void ScavTrap::guardGate()
{
	if (mHitPoints <= 0 || mEnergyPoints <= 0)
	{
		return ;
	}
	std::cout << "ScavTrap " << mName << " is on Guard mode" << std::endl;
}
