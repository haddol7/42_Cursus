/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 01:19:30 by daeha             #+#    #+#             */
/*   Updated: 2024/10/15 19:13:49 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
	try
	{
		Bureaucrat daeha("daeha", 1);
	
		std::cout << daeha << std::endl;
		daeha.IncrementGrade();
	}
	catch (const Bureaucrat::GradeTooHighException &e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const Bureaucrat::GradeTooLowException &e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const std::exception& e) 
	{
        std::cerr << "Caught a general exception: " << e.what() << std::endl;
    }
	return (0);
}
