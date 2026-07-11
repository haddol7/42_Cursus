/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:01:59 by daeha             #+#    #+#             */
/*   Updated: 2024/09/29 23:05:31 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class Weapon
{
public:
	Weapon();
	Weapon(std::string name);
	~Weapon();
	const std::string& getType(void);
	void setType(std::string name);
private:
	std::string type;
};
