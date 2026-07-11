/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:35:15 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 22:01:26 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Constructor : Brain" << std::endl;
}

Brain::Brain(const Brain& copy)
{
	std::cout << "Copy Constructor : Brain" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		ideas[i] = copy.ideas[i];
	}
}

Brain& Brain::operator=(const Brain& rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < 100; i++)
		{
			ideas[i] = rhs.ideas[i];
		}
	}
	return (*this);
}

Brain::~Brain()
{
	std::cout << "Destructor : Brain" << std::endl;
}

void Brain::setIdea(const int idx, const std::string& str)
{
	if (idx >= 0 && idx <= 99)
	{
		ideas[idx] = str;
	}
}

const std::string& Brain::getIdea(const int idx) const
{
	static const std::string empty = "";
	
	if (idx >= 0 && idx <= 99)
	{
		return (ideas[idx]);
	}
	return (empty);
}
