/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:02:31 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 20:24:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "ICharacter.hpp"
#include "AMateria.hpp"

#define NULLPTR (0)
#define MAX_CAP (4)
class Character : public ICharacter
{
public:
	Character();
	~Character();
	Character(const Character& copy);
	Character& operator=(const Character& rhs);

	Character(const std::string& name);
	const std::string& getName() const;
	void equip(AMateria* m);
	void unequip(int idx);
	void use(int idx, ICharacter& target);

private:
	AMateria*	mMaterias[4];
	AMateria*	mFloor[4];
	std::string	mName;
};
