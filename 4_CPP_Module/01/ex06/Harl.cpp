/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:49:06 by daeha             #+#    #+#             */
/*   Updated: 2024/09/30 15:29:07 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl()
{
}

Harl::~Harl()
{
}

void Harl::debug()
{
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger." << std::endl;
	std::cout << "I really do!" << std::endl << std::endl;
}

void Harl::info()
{
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money." << std::endl; 
	std::cout << "You didn’t put enough bacon in my burger!" << std::endl;
	std::cout << "If you did, I wouldn’t be asking for more!" << std::endl << std::endl;
}

void Harl::warning()
{
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free." << std::endl;
	std::cout << "I’ve been coming for years whereas you started working here since last month." << std::endl << std::endl;
}

void Harl::error()
{
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl << std::endl;
}

void Harl::complain(std::string level)
{
	void (Harl::*func[4])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	std::string	mode_str[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	for(int i = 0; i < 4; i++)
	{
		if (level == mode_str[i])
		{
			(this->*func[i])();
			return ;
		}
	}
	std::cout << "Invalid Mode selection" << std::endl;
}

bool Harl::filter(const std::string& level) 
{
	int			iLevel = 0;
	std::string	mode_str[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	while (iLevel < 4)
	{
		if (level == mode_str[iLevel])
			break;
		iLevel++;
	}
	if (iLevel == 4)
		return (false);
	switch (iLevel)
	{
		case 0:
			debug();
		case 1:
			info();
		case 2:
			warning();
		case 3:
			error();
	}
	return (true);
}
