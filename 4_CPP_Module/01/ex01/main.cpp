/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 20:37:22 by daeha             #+#    #+#             */
/*   Updated: 2024/09/29 21:38:15 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	Zombie *daeha = zombieHorde(10, "daeha");

	for (int i = 0; i < 10; i++)
	{
		daeha[i].announce();
	}
	delete[] daeha;
	return (0);
}
