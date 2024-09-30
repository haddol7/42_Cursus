/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:38:22 by daeha             #+#    #+#             */
/*   Updated: 2024/10/01 00:07:23 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Point.hpp"

int main ( void )
{
	if (bsp(Point(-3, 0), Point(3, 0), Point(0, 5), Point(0, 5)))
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	return 0;
}
