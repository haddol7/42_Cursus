/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 20:37:22 by daeha             #+#    #+#             */
/*   Updated: 2024/09/29 21:09:59 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	Zombie *daeha = newZombie("daeha");

	daeha->announce();
	randomChump("one");
	randomChump("two");
	randomChump("three");

	delete daeha;
	return (0);
}
