/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:37:46 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 02:36:18 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

#include "DiamondTrap.hpp"

int main( void )
{
    DiamondTrap daeha("daeha");

	std::cout << "=============================" << std::endl;
    daeha.whoAmI();

    daeha.attack("CPP03");
    daeha.takeDamage(10);
    daeha.highFivesGuys();
    daeha.guardGate();
	std::cout << "=============================" << std::endl;
    return 0;
}
