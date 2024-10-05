/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:50:06 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 02:37:00 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap
{
public:
	DiamondTrap();
	DiamondTrap(const DiamondTrap& copy);
	~DiamondTrap();
	DiamondTrap& operator=(const DiamondTrap& rhs);
	DiamondTrap(const std::string& name);
	void whoAmI();
	using ClapTrap::attack;
	
private:
	std::string mName;
};
