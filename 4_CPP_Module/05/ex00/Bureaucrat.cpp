/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 00:01:03 by daeha             #+#    #+#             */
/*   Updated: 2024/10/15 19:14:17 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
	: mName("Default")
	, mGrade(1)
{
}

Bureaucrat::Bureaucrat(const std::string& name, const int grade)
	: mName(name)
	, mGrade(grade)
{
	if (GetGrade() < HIGHEST_GRADE)
	{
		throw (Bureaucrat::GradeTooHighException());
	}
	else if (GetGrade() > LOWEST_GRADE)
	{
		throw (Bureaucrat::GradeTooLowException());
	}
}

Bureaucrat::Bureaucrat(const Bureaucrat& copy)
	: mName(copy.GetName())
	, mGrade(copy.GetGrade())
{
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& rhs)
{
	if (this != &rhs)
	{
		mGrade = rhs.GetGrade();
	}
	return (*this);
}

Bureaucrat::~Bureaucrat()
{
}

const std::string& Bureaucrat::GetName(void) const
{
	return (mName);
}

int Bureaucrat::GetGrade(void) const
{
	return (mGrade);
}

void Bureaucrat::IncrementGrade(void)
{
	if (GetGrade() == HIGHEST_GRADE)
	{
		throw (Bureaucrat::GradeTooHighException());
	}
	mGrade--;
}

void Bureaucrat::DecrementGrade(void)
{
	if (GetGrade() == LOWEST_GRADE)
	{
		throw (Bureaucrat::GradeTooLowException());
	}
	mGrade++;
}

std::ostream& operator<<(std::ostream& out, const Bureaucrat& rhs)
{
	out << rhs.GetName() << ", bureaucrat grade " << rhs.GetGrade() << "." << std::flush;
	
	return (out);
}
