/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:08:21 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 22:12:01 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AAnimal.hpp"
#include "Brain.hpp"

class Cat : public AAnimal
{
public:
	Cat();
	~Cat();
	Cat(const Cat& copy);
	Cat& operator=(const Cat& rhs);
	void makeSound() const;
	const std::string& getBrainIdea(const int idx) const;
	void setBrainIdea(const int idx, const std::string& str);
private:
	Brain* mBrain;
};


