/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:42:41 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 02:06:36 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap()
	: ClapTrap("defualt", 100, 100, 30)
{
	std::cout << "FragTrap Constructor : default" << std::endl;
}

FragTrap::FragTrap(const std::string& name)
	: ClapTrap(name, 100, 100, 30)
{
	std::cout << "FragTrap Constructor : " << name << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap Destructor : " << mName << std::endl;
}

FragTrap::FragTrap(const FragTrap& copy)
	: ClapTrap(copy.mName, copy.mHitPoints, copy.mEnergyPoints, copy.mAttackDamage)
{
	std::cout << "FragTrap Copy Constructor : " << mName << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& rhs)
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

void FragTrap::highFivesGuys()
{
	if (mHitPoints <= 0 || mEnergyPoints <= 0)
	{
		return ;
	}
	std::cout << "FragTrap " << mName << " suggests highfive!" << std::endl;
}
