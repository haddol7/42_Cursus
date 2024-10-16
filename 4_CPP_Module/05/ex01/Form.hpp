#pragma once

#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"

class Bureaucrat;

# define HIGHEST_GRADE (1)
# define LOWEST_GRADE (150)

class Form
{
public:
	Form();
	Form(const std::string& name, int grade);
	~Form();
	Form(const Form& copy);
	Form& operator=(const Form& rhs);

	const std::string& GetName(void) const;
	bool GetSign(void) const;
	int GetGradeToSign(void) const;
	int GetGradeToExecute(void) const;
	
	void beSigned(const Bureaucrat& bureaucrat);

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
	bool				mSign;
	const int			mGradeToSign;
	const int			mGradeToExecute;
};

std::ostream& operator<<(std::ostream& out, const Form& rhs);
