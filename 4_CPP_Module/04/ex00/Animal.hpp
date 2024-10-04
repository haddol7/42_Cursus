/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:53:18 by daeha             #+#    #+#             */
/*   Updated: 2024/10/03 22:06:11 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Animal
{
public:
	Animal();
	Animal(const std::string& type);
	Animal& operator=(const Animal& lhs);
	Animal(const Animal& copy);
	virtual ~Animal();
	virtual void makeSound() const;
	std::string getType() const;
	void SetType(const std::string& type);
protected:
	std::string type;
};
