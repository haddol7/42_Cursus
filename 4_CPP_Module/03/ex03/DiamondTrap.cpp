/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:12:38 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 02:33:46 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
	: ClapTrap("defult_clap_name")
	, FragTrap("default")
	, ScavTrap("default")
	, mName("default")
{
	FragTrap::mHitPoints = 100;
    ScavTrap::mEnergyPoints = 50;
    FragTrap::mAttackDamage = 30;
	std::cout << "DiamodTrap Constructor : default" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string& name)
	: ClapTrap(name + "_clap_name")
	, FragTrap(name)
	, ScavTrap(name)
	, mName(name)
{
	FragTrap::mHitPoints = 100;
    ScavTrap::mEnergyPoints = 50;
    FragTrap::mAttackDamage = 30;
	std::cout << "DiamodTrap Constructor : " << mName << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& copy)
	: ClapTrap(copy)
	, FragTrap(copy)
	, ScavTrap(copy)
	, mName(copy.mName)
{
	std::cout << "DiamodTrap Constructor : " << mName << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamodTrap Destructor : " << mName << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& rhs)
{
	if (this != &rhs)
	{
		ClapTrap::mName = rhs.ClapTrap::mName;
		mName = rhs.mName;
		mHitPoints = rhs.mHitPoints;
		mEnergyPoints = rhs.mEnergyPoints;
		mAttackDamage = rhs.mAttackDamage;
	}
	return (*this);
}

void DiamondTrap::whoAmI()
{
	if (mHitPoints <= 0 || mEnergyPoints <= 0)
	{
		return ;
	}
	std::cout << mName << " - " << ClapTrap::mName << std::endl;
}
