/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:08:21 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 21:40:36 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
public:
	Dog();
	~Dog();
	Dog(const Dog& copy);
	Dog& operator=(const Dog& rhs);
	void makeSound() const;
	const std::string& getBrainIdea(const int idx) const;
	void setBrainIdea(const int idx, const std::string& str);
private:
	Brain *mBrain;
};


