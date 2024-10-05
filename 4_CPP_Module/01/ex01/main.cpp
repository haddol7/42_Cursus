/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 20:37:22 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 00:33:57 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Zombie.hpp"

int main(void)
{
	Zombie *daeha = zombieHorde(10, "daeha");
	std::string	name;

	for (int i = 0; i < 10; i++)
	{	
		name = std::to_string(i) + "-" + daeha[i].getName();
		daeha[i].setName(name);
		daeha[i].announce();
	}
	delete[] daeha;
	return (0);
}
