/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:01:23 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 22:38:18 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "Character.hpp" //MAX_CAP

MateriaSource::MateriaSource()
{
	for (int i = 0; i < MAX_CAP; i++)
	{
		mMaterias[i] = NULLPTR;
	}
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < MAX_CAP; i++)
	{
		delete mMaterias[i];
	}
}

MateriaSource::MateriaSource(const MateriaSource& copy)
{
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

MateriaSource& MateriaSource::operator=(const MateriaSource& rhs)
{
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

void MateriaSource::learnMateria(AMateria *m)
{
	for (int i = 0; i < MAX_CAP; i++)
	{
		if (mMaterias[i] == NULLPTR)
		{
			mMaterias[i] = m;
			return ;
		}
	}
	delete m;
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < MAX_CAP; i++)
	{
		if (mMaterias[i] && mMaterias[i]->getType() == type)
		{
			return (mMaterias[i]->clone());
		}
	}
	return (NULL);
}
