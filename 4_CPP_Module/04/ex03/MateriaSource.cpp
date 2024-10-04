/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:01:23 by daeha             #+#    #+#             */
/*   Updated: 2024/10/04 21:53:39 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; i++)
	{
		mMaterias[i] = NULL;
	}
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < 4; i++)
	{
		delete mMaterias[i];
	}
}

MateriaSource::MateriaSource(const MateriaSource& copy)
{
	for (int i = 0; i < 4; i++)
	{
		mMaterias[i] = copy.mMaterias[i]->clone();
	}
}

MateriaSource& MateriaSource::operator=(const MateriaSource& lhs)
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

void MateriaSource::learnMateria(AMateria *m)
{
	for (int i = 0; i < 4; i++)
	{
		if (mMaterias[i] == NULL)
		{
			mMaterias[i] = m;
			return ;
		}
	}
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < 4; i++)
	{
		if (mMaterias[i] && mMaterias[i]->getType() == type)
		{
			return (mMaterias[i]->clone());
		}
	}
	return (NULL);
}
