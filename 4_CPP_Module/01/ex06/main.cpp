/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:04:22 by daeha             #+#    #+#             */
/*   Updated: 2024/09/30 15:15:29 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int argc, char *argv[])
{
	Harl	harl;

	if (argc != 2 || harl.filter(argv[1]) == false)
	{
		std::cerr << "[ Probably complaining about insignificant problems ]" << std::endl;
		return (1);
	}
	return (0);
}
