/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:01:42 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 23:32:20 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "MateriaSource.hpp"
#include "Character.hpp"
#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

// void leaks(void)
// {
// 	system("leaks ex03");
// }

int main()
{
	//atexit(leaks);
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* me = new Character("me");

	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter* bob = new Character("bob");

	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;
	
	return 0;
}

// int main()
// {
// 	atexit(leaks);
// 	IMateriaSource* skill_tree = new MateriaSource();
// 	skill_tree->learnMateria(new Ice());
// 	skill_tree->learnMateria(new Cure());
// 	skill_tree->learnMateria(new Ice());
// 	skill_tree->learnMateria(new Ice());

// 	Character*	healer = new Character("daeha");
// 	healer->equip(skill_tree->createMateria("cure"));
// 	healer->equip(skill_tree->createMateria("cure"));
// 	healer->equip(skill_tree->createMateria("cure"));
// 	healer->equip(skill_tree->createMateria("cure"));
	
// 	Character	mage(*healer);
// 	mage.unequip(0);
// 	mage.unequip(1);
// 	mage.unequip(2);
// 	mage.unequip(10);	//아무 행동도 안함
// 	mage.unequip(-10);	//아무 행동도 안함
// 	mage.unequip(0);	//아무 행동도 안함
// 	//[3]번에 cure만 남게됨

// 	mage.equip(skill_tree->createMateria("ice"));	//unequip한 3개가 delete됨
// 	mage.equip(skill_tree->createMateria("ice"));
// 	mage.equip(skill_tree->createMateria("ice"));
// 	mage.equip(skill_tree->createMateria("ice"));	//ice가 delete됨
// 	mage.equip(skill_tree->createMateria("FIREBALL"));	//아무 행동도 안함

// 	std::cout << "==========healer==========" << std::endl;
// 	healer->use(0, mage);
// 	healer->use(1, mage);
// 	healer->use(2, mage);
// 	healer->use(3, mage);
// 	std::cout << "==========mage==========" << std::endl;
// 	mage.use(0, *healer);
// 	mage.use(1, *healer);
// 	mage.use(2, *healer);
// 	mage.use(3, *healer);

// 	healer->unequip(0);
// 	healer->equip(skill_tree->createMateria("ice"));

// 	*healer = mage;
// 	healer->unequip(0);
// 	healer->unequip(1);
// 	healer->unequip(2);
// 	healer->equip(skill_tree->createMateria("cure"));
// 	healer->equip(skill_tree->createMateria("cure"));
// 	healer->equip(skill_tree->createMateria("cure"));
// 	healer->equip(skill_tree->createMateria("ice"));
// 	healer->equip(skill_tree->createMateria("ice"));
// 	std::cout << "==========healer==========" << std::endl;
// 	healer->use(0, mage);
// 	healer->use(1, mage);
// 	healer->use(2, mage);
// 	healer->use(3, mage);
	
// 	delete healer;
// 	delete skill_tree;
// 	return (0);
// }
