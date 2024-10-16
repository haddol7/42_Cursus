#pragma once

#include <iostream>
#include <exception>
#include "Form.hpp"

# define HIGHEST_GRADE (1)
# define LOWEST_GRADE (150)

class Form;

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

	void signForm(Form& form) const;

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
