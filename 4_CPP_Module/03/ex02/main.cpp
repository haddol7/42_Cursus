/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:37:46 by daeha             #+#    #+#             */
/*   Updated: 2024/10/08 15:13:37 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int main( void )
{
	{
		FragTrap daeha("daeha");

		daeha.attack("CPP 03 ex01");
		daeha.highFivesGuys();
		daeha.beRepaired(100); //100
		daeha.takeDamage(100); //0
		daeha.attack("CPP 03 ex01");
		daeha.highFivesGuys();
	}
	std::cout << std::endl;
	{
		ClapTrap *old_daeha = new FragTrap("old daeha");
			
		old_daeha->attack("CPP 03 ex01");
		//old_daeha->guardGate();
		old_daeha->beRepaired(100); //100
		old_daeha->takeDamage(30); //0
		old_daeha->attack("CPP 03 ex01");
		//old_daeha->guardGate();
		delete old_daeha;
	}
    return (0);
}
