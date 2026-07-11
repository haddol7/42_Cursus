/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:38:22 by daeha             #+#    #+#             */
/*   Updated: 2024/10/07 20:32:20 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Point.hpp"

int main ( void )
{
	Point test[12] = { 
						Point(0, 0),			//D : false
						Point(-1.25, 7.3),		//E : true
						Point(0, 2),			//F : true
						Point(3, 1.98),			//G : true
						Point(4, -5),			//H : false
						Point(-3.36264,5.57631),//I : false
						Point(-1.57359,4.2877),	//J : true
						Point(-4.02571,1.34767),//K : false
						Point(2.44771,4.52132),	//L : false
						Point(-4.13067,4.18693),//M : true
						Point(2.8, 5.8),		//N : false
						Point(-1.32,7.46)		//A : false
					};			
	
	for (int i = 0; i < 12; i++)
	{
		if (bsp(Point(-1.32,7.46), Point(-5.76,2.6), Point(3.66,1.22), test[i]))
		{
			std::cout << "True" << std::endl;
		}
		else
		{
			std::cout << "False" << std::endl;
		}
	}
	return 0;
}
