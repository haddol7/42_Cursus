/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:13:02 by daeha             #+#    #+#             */
/*   Updated: 2024/10/08 22:59:43 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"

// void leaks()
// {
// 	system("leaks ex01");
// }

int main( void )
{	
//	atexit(leaks);
    const Animal* j = new Dog();
    const Animal* i = new Cat();

	std::cout << std::endl;
    delete j;//should not create a leak
	delete i;
	std::cout << std::endl;
    Dog basic;
    {
        Dog tmp = basic;
    }
	std::cout << "============loop============" << std::endl;
    const Animal* animals[4] = { new Dog(), new Dog(), new Cat(), new Cat() };
	std::cout << std::endl;
    for ( int i = 0; i < 4; i++ ) {
        delete animals[i];
    }
	std::cout << std::endl;
    return 0;
}
