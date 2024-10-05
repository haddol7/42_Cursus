/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 20:37:22 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 00:24:43 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	Zombie *daeha = newZombie("daeha");
	Zombie test("test");

	test.announce();
	daeha->announce();
	delete daeha;
	randomChump("one");
	randomChump("two");
	randomChump("three");

	return (0);
}
