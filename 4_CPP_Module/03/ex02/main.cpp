/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:37:46 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 02:17:20 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int main( void )
{
    FragTrap daeha("daeha");

    daeha.attack("cpp 03");
    daeha.takeDamage(10);
    daeha.beRepaired(10);
    daeha.highFivesGuys();

    return (0);
}
