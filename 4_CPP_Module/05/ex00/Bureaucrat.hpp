/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 00:01:05 by daeha             #+#    #+#             */
/*   Updated: 2024/10/11 01:29:51 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <exception>

# define HIGHEST_GRADE (1)
# define LOWEST_GRADE (150)

class Bureaucrat
{
public:
	Bureaucrat();
	Bureaucrat(const std::string& name, const int grade);
	Bureaucrat(const Bureaucrat& copy);
	Bureaucrat& operator=(const Bureaucrat& rhs);
	~Bureaucrat();
	
	const std::string& GetName(void) const;
	int GetGrade(void) const;
	void IncrementGrade(void);
	void DecrementGrade(void);

	class GradeTooHighException : public std::exception 
	{
	public:
		virtual const char* what() const throw()
		{
			return ("Grade Too HIGH");
		}
	};
	class GradeTooLowException : public std::exception 
	{
	public:
		virtual const char* what() const throw()
		{
			return ("Grade Too LOW");
		}
	};

private:
	const std::string	mName;
	int					mGrade;
};

std::ostream& operator<<(std::ostream& out, const Bureaucrat& rhs);
