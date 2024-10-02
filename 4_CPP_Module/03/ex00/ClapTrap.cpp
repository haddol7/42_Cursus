/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:42:41 by daeha             #+#    #+#             */
/*   Updated: 2024/10/02 18:43:38 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
	: mName("default")
	, mHitPoints(10)
	, mEnergyPoints(10)
	, mAttackDamage(0)
{
	std::cout << "Constructor : default" << std::endl;
}

ClapTrap::ClapTrap(const std::string& name)
	: mName(name)
	, mHitPoints(10)
	, mEnergyPoints(10)
	, mAttackDamage(0)
{
	std::cout << "Constructor : " << name << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << "Destructor : " << mName << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& copy)
	: mName(copy.mName)
	, mHitPoints(copy.mHitPoints)
	, mEnergyPoints(copy.mEnergyPoints)
	, mAttackDamage(copy.mAttackDamage)
{
	std::cout << "Copy Constructor : " << mName << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& rhs)
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

void ClapTrap::attack(const std::string& target)
{
	if (mHitPoints <= 0 || mEnergyPoints <= 0)
	{
		std::cout << mName << " is down ..." << std::endl;
		return ;
	}
	std::cout << "ClapTrap " << mName << " attacks " << target << ", causing " << mAttackDamage << " points of damage!" << std::endl;
	mEnergyPoints--;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap " << mName << " takes " << amount << " points of damage!" << std::endl;
	if (mHitPoints <= amount)
	{
		std::cout << mName << " is down ..." << std::endl;
		mHitPoints = 0;
	}
	else
		mHitPoints -= amount;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (mHitPoints <= 0 || mEnergyPoints <= 0)
	{
		std::cout << mName << " is down ..." << std::endl;
		return ;
	}
	std::cout << "ClapTrap " << mName << " repaires " << amount << " points of points by itself!" << std::endl;
	mEnergyPoints--;
}
