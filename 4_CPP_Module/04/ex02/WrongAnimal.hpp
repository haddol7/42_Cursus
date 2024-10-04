/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:53:18 by daeha             #+#    #+#             */
/*   Updated: 2024/10/03 22:13:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class WrongAnimal
{
public:
	WrongAnimal();
	WrongAnimal(const std::string& type);
	WrongAnimal& operator=(const WrongAnimal& lhs);
	WrongAnimal(const WrongAnimal& copy);
	~WrongAnimal();
	void makeSound() const;
	std::string getType() const;
	void SetType(const std::string& type);
protected:
	std::string type;
};
