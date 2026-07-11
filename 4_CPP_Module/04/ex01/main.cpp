/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:13:02 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 22:06:12 by daeha            ###   ########.fr       */
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

	std::cout << "============loop============" << std::endl;
    const Animal* animals[4] = { new Dog(), new Dog(), new Cat(), new Cat() };
	std::cout << std::endl;
    for ( int i = 0; i < 4; i++ ) {
        delete animals[i];
    }
	std::cout << std::endl;
    return 0;
}

// int main( void )
// {	
// 	// atexit(leaks);
//     Dog* ddobbi = new Dog();

// 	std::cout << std::endl;
// 	ddobbi->setBrainIdea(0, "Go for a Walk");
// 	ddobbi->setBrainIdea(10, "Bark");
// 	ddobbi->setBrainIdea(11, "Eat some human's food");
// 	for (int i = 0; i < 100; i++)
// 	{
// 		if (ddobbi->getBrainIdea(i).empty() == true)
// 		{
// 			continue;
// 		}
// 		std::cout << ddobbi->getBrainIdea(i) << std::endl;
// 	}
// 	std::cout << std::endl;

// 	Dog baduk = *ddobbi;
	
// 	baduk.setBrainIdea(-10, "WICKED THINK");
// 	baduk.setBrainIdea(1, "Sleep");
	
// 	std::cout << baduk.getBrainIdea(-10) << std::endl;
// 	for (int i = 0; i < 100; i++)
// 	{
// 		if (baduk.getBrainIdea(i).empty() == true)
// 		{
// 			continue;
// 		}
// 		std::cout << baduk.getBrainIdea(i) << std::endl;
// 	}
	
// 	std::cout << std::endl;
//     delete ddobbi;
//     return 0;
// }
