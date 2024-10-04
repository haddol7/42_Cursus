/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:52:13 by daeha             #+#    #+#             */
/*   Updated: 2024/10/04 21:49:19 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character()
	: mName("")
{
	for (int i = 0 ; i < 4 ; i++)
	{
		mMaterias[i] = NULL;
	}
}

Character::~Character()
{
	for (int i = 0 ; i < 4 ; i++)
	{
		delete  mMaterias[i];
	}
}

Character::Character(const Character& copy)
	: mName(copy.getName())
{
	for (int i = 0; i < 4; i++)
	{
		mMaterias[i] = copy.mMaterias[i]->clone();
	}
}

Character& Character::operator=(const Character& lhs)
{
	if (this != &lhs)
	{
		for (int i = 0; i < 4; i++)
		{
			delete mMaterias[i];
			mMaterias[i] = lhs.mMaterias[i]->clone();
		}
	}
	return (*this);
}

Character::Character(const std::string& name)
	: mName(name)
{
}

const std::string& Character::getName() const
{
	return (mName);
}

void Character::equip(AMateria* m)
{
	for(int i = 0; i < 4; i++)
	{
		if (mMaterias[i] == NULL)
		{
			mMaterias[i] = m;
			return ;
		}
	}
}

void Character::unequip(int idx)
{
	if (idx >= 0 && idx <= 3)
	{
		if (mMaterias[idx] != NULL)
		{
			mMaterias[idx] = NULL;
		}
	}
}

void Character::use(int idx, ICharacter& target)
{
	if (idx >= 0 && idx <= 3 && mMaterias[idx] != NULL)
	{
		mMaterias[idx]->use(target);
	}
	else
	{
		std::cout << "NOPE" << std::endl;
	}
}
