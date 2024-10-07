/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:37:46 by daeha             #+#    #+#             */
/*   Updated: 2024/10/07 23:29:08 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main(void)
{
	ClapTrap daeha("daeha");

	daeha.attack("CPP 03");
	daeha.takeDamage(3); //7
	daeha.beRepaired(10); //10
	daeha.takeDamage(10); //0
	daeha.takeDamage(10); //0
	daeha.attack("Nothing"); //0
	
	return (0);
}
