/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:53:18 by daeha             #+#    #+#             */
/*   Updated: 2024/10/03 23:21:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class AAnimal
{
public:
	AAnimal();
	AAnimal(const std::string& type);
	AAnimal& operator=(const AAnimal& lhs);
	AAnimal(const AAnimal& copy);
	virtual ~AAnimal();
	virtual void makeSound() const = 0;
	std::string getType() const;
	void SetType(const std::string& type);
protected:
	std::string type;
};
