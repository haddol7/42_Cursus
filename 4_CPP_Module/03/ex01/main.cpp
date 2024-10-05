/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:37:46 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 02:17:30 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main( void )
{
    ScavTrap daeha("daeha");
    ScavTrap clone(daeha);

    daeha.attack("cpp 03");
    daeha.beRepaired(10);
    daeha.takeDamage(10);
    daeha.guardGate();

    return (0);
}
