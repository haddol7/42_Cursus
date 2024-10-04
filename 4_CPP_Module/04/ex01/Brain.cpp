/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:35:15 by daeha             #+#    #+#             */
/*   Updated: 2024/10/03 22:40:36 by daeha            ###   ########.fr       */
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

Brain& Brain::operator=(const Brain& lhs)
{
	if (this != &lhs)
	{
		for (int i = 0; i < 100; i++)
		{
			ideas[i] = lhs.ideas[i];
		}
	}
	return (*this);
}

Brain::~Brain()
{
	std::cout << "Destructor : Brain" << std::endl;
}
