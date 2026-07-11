/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:08:21 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 22:11:16 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal
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


