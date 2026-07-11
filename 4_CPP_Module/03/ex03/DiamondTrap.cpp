/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:12:38 by daeha             #+#    #+#             */
/*   Updated: 2024/10/08 16:11:04 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
	: ClapTrap("defult_clap_name")
	, FragTrap("defult_clap_name")
	, ScavTrap("defult_clap_name")
	, mName("default")
{
	FragTrap::mHitPoints = 100;
	ScavTrap::mEnergyPoints = 50;
	FragTrap::mAttackDamage = 30;
	FragTrap::mMaxHitPoints = 100;
	std::cout << "DiamodTrap Constructor : default" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string& name)
	: ClapTrap(name + "_clap_name")
	, FragTrap(name + "_clap_name")
	, ScavTrap(name + "_clap_name")
	, mName(name)
{
	FragTrap::mHitPoints = 100;
	ScavTrap::mEnergyPoints = 50;
	FragTrap::mAttackDamage = 30;
	FragTrap::mMaxHitPoints = 100;
	std::cout << "DiamodTrap Constructor : " << mName << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& copy)
	: ClapTrap(copy)
	, FragTrap(copy)
	, ScavTrap(copy)
	, mName(copy.mName)
{
	FragTrap::mHitPoints = copy.FragTrap::mHitPoints;
	ScavTrap::mEnergyPoints = copy.ScavTrap::mEnergyPoints;
	FragTrap::mAttackDamage = copy.FragTrap::mAttackDamage;
	FragTrap::mMaxHitPoints = copy.FragTrap::mMaxHitPoints;
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
		FragTrap::mHitPoints = rhs.FragTrap::mHitPoints;
		ScavTrap::mEnergyPoints = rhs.ScavTrap::mEnergyPoints;
		FragTrap::mAttackDamage = rhs.FragTrap::mAttackDamage;
		FragTrap::mMaxHitPoints = rhs.FragTrap::mMaxHitPoints;
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
