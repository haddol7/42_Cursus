/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:52:13 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 22:36:32 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character()
	: mName("")
{
	for (int i = 0; i < MAX_CAP; i++)
	{
		mMaterias[i] = NULLPTR;
	}
	for (int i = 0; i < MAX_CAP; i++)
	{
		mFloor[i] = NULLPTR;
	}
}

Character::~Character()
{
	for (int i = 0; i < MAX_CAP; i++)
	{
		delete  mMaterias[i];
	}
	for (int i = 0; mFloor[i] != NULLPTR && i < MAX_CAP; i++)
	{
		delete mFloor[i];
	}
}

Character::Character(const Character& copy)
	: mName(copy.getName())
{
	for (int i = 0; mFloor[i] != NULLPTR && i < MAX_CAP; i++)
	{
		delete mFloor[i];
		mFloor[i] = NULLPTR;
	}
	for (int i = 0; i < MAX_CAP; i++)
	{
		if (copy.mMaterias[i] != NULLPTR)
		{
			mMaterias[i] = copy.mMaterias[i]->clone();
		}
		else
		{
			mMaterias[i] = NULLPTR;
		}
	}
}

Character& Character::operator=(const Character& rhs)
{
	for (int i = 0; mFloor[i] != NULLPTR && i < MAX_CAP; i++)
	{
		delete mFloor[i];
		mFloor[i] = NULLPTR;
	}
	if (this != &rhs)
	{
		for (int i = 0; i < MAX_CAP; i++)
		{
			delete mMaterias[i];
			if (rhs.mMaterias[i] != NULLPTR)
			{
				mMaterias[i] = rhs.mMaterias[i]->clone();
			}
			else
			{
				mMaterias[i] = NULLPTR;
			}
		}
	}
	return (*this);
}

Character::Character(const std::string& name)
	: mName(name)
{
	for (int i = 0; i < MAX_CAP; i++)
	{
		mMaterias[i] = NULLPTR;
	}
	for (int i = 0; i < MAX_CAP; i++)
	{
		mFloor[i] = NULLPTR;
	}
}

const std::string& Character::getName() const
{
	return (mName);
}

void Character::equip(AMateria* m)
{
	if (m == NULLPTR)
	{
		return ;
	}
	//쓰레기통에 모든 materia를 delete해준다.
	for (int i = 0; mFloor[i] != NULLPTR && i < MAX_CAP; i++)
	{
		delete mFloor[i];
		mFloor[i] = NULLPTR;
	}
	for(int i = 0; i < MAX_CAP; i++)
	{
		if (mMaterias[i] == NULLPTR)
		{
			mMaterias[i] = m;
			return ;
		}
	}
	delete m;
}

void Character::unequip(int idx)
{
	if (idx >= 0 && idx <= 3 && mMaterias[idx] != NULLPTR)
	{
		for (int i = 0; i < MAX_CAP; i++)
		{
			if (mFloor[i] == NULLPTR)
			{
				mFloor[i] = mMaterias[idx];
				mMaterias[idx] = NULLPTR;
				return ;
			}	
		}
		//올바른 idx일 경우 항상 mFloor 안에 materia가 들어가야 함
		//assert(true && "Invalid unequip");
	}
}

void Character::use(int idx, ICharacter& target)
{
	if (idx >= 0 && idx <= 3 && mMaterias[idx] != NULLPTR)
	{
		mMaterias[idx]->use(target);
	}
}
